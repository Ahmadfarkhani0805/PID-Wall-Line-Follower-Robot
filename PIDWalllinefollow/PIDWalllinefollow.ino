// --- PIN MOTOR ---
const int IN1_KANAN = 25; const int IN2_KANAN = 33; const int ENA_KANAN = 17; 
const int IN3_KIRI = 26;  const int IN4_KIRI = 27;  const int ENB_KIRI = 16; 

// --- PIN SENSOR ---
const int SENSOR_KIRI = 34; const int SENSOR_KANAN = 32; // Hanya 2 Sensor
const int TRIG_DEPAN = 14;  const int ECHO_DEPAN = 12;
const int TRIG_KIRI = 13;   const int ECHO_KIRI = 23;

// --- STATE MACHINE ---
enum RobotState { LINE_FOLLOWER, AVOID_MANEUVER, WALL_FOLLOWER };
RobotState currentState = LINE_FOLLOWER;

// ================= VARIABEL PID =================
int baseSpeed = 150; 

// PID Line Follower (TUNE NILAI INI!)
float Kp_Line = 35.0; 
float Ki_Line = 0.0;  
float Kd_Line = 15.0;
int lastError_Line = 0;
int I_Line = 0;

// PID Wall Follower (TUNE NILAI INI!)
float targetJarakDinding = 8.0; 
float Kp_Wall = 15.0;
float Ki_Wall = 0.0;
float Kd_Wall = 10.0;
float lastError_Wall = 0;
float I_Wall = 0;

void setup() {
  Serial.begin(115200);
  pinMode(IN1_KANAN, OUTPUT); pinMode(IN2_KANAN, OUTPUT); pinMode(ENA_KANAN, OUTPUT);
  pinMode(IN3_KIRI, OUTPUT); pinMode(IN4_KIRI, OUTPUT); pinMode(ENB_KIRI, OUTPUT);
  
  pinMode(SENSOR_KIRI, INPUT); pinMode(SENSOR_KANAN, INPUT);
  
  pinMode(TRIG_DEPAN, OUTPUT); pinMode(ECHO_DEPAN, INPUT);
  pinMode(TRIG_KIRI, OUTPUT); pinMode(ECHO_KIRI, INPUT);
}

void loop() {
  switch (currentState) {
    case LINE_FOLLOWER:
      jalankanPIDLineFollower();
      cekRintanganDepan();
      break;

    case AVOID_MANEUVER:
      gerakMotor(0, 0); delay(500);
      
      // Belok Kanan 90 Derajat (Kotak ada di Kiri robot)
      gerakMotor(baseSpeed, -baseSpeed); 
      delay(550); // Sesuaikan waktu ini saat ujicoba
      
      // Maju sedikit menjauhi garis
      gerakMotor(baseSpeed, baseSpeed);  
      delay(400);
      
      currentState = WALL_FOLLOWER;
      lastError_Wall = 0; I_Wall = 0;
      break;

    case WALL_FOLLOWER:
      jalankanPIDWallFollower();
      cekKembaliKeGaris();
      break;
  }
}

// ================= FUNGSI KONTROL MOTOR =================
void gerakMotor(int speedKiri, int speedKanan) {
  speedKiri = constrain(speedKiri, -255, 255);
  speedKanan = constrain(speedKanan, -255, 255);

  if (speedKiri >= 0) {
    digitalWrite(IN3_KIRI, HIGH); digitalWrite(IN4_KIRI, LOW); analogWrite(ENB_KIRI, speedKiri);
  } else {
    digitalWrite(IN3_KIRI, LOW); digitalWrite(IN4_KIRI, HIGH); analogWrite(ENB_KIRI, -speedKiri);
  }

  if (speedKanan >= 0) {
    digitalWrite(IN1_KANAN, HIGH); digitalWrite(IN2_KANAN, LOW); analogWrite(ENA_KANAN, speedKanan);
  } else {
    digitalWrite(IN1_KANAN, LOW); digitalWrite(IN2_KANAN, HIGH); analogWrite(ENA_KANAN, -speedKanan);
  }
}

float bacaJarak(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); 
  if (duration == 0) return 999.0; 
  return (duration * 0.0343) / 2.0; 
}

// ================= STATE: LINE FOLLOWER (2 SENSOR) =================
void jalankanPIDLineFollower() {
  // Asumsi: Hitam = HIGH (1), Putih = LOW (0)
  bool kiri = digitalRead(SENSOR_KIRI);
  bool kanan = digitalRead(SENSOR_KANAN);
  
  int error = 0;

  // 1. Kondisi Persimpangan (+) -> Bypass PID, Paksa Maju Lurus
  if (kiri && kanan) {
    gerakMotor(baseSpeed, baseSpeed);
    return; 
  }

  // 2. Pemetaan Error 2 Sensor (Mengapit Garis)
  if (!kiri && !kanan) {
    // Keduanya putih. Bisa berarti lurus pas di tengah, atau terlepas dari garis.
    if (lastError_Line == 0) error = 0; 
    else if (lastError_Line < 0) error = -2; // Loss line ke kanan -> paksa belok kiri tajam
    else if (lastError_Line > 0) error = 2;  // Loss line ke kiri -> paksa belok kanan tajam
  }
  else if (kiri && !kanan) {
    error = -1; // Garis ada di kiri robot -> Koreksi ke Kiri
  }
  else if (!kiri && kanan) {
    error = 1;  // Garis ada di kanan robot -> Koreksi ke Kanan
  }

  // 3. Kalkulasi PID
  int P = error;
  I_Line = I_Line + error;
  int D = error - lastError_Line;
  
  int PID_Value = (Kp_Line * P) + (Ki_Line * I_Line) + (Kd_Line * D);
  lastError_Line = error;

  // 4. Terapkan ke Motor
  int speedKiri = baseSpeed + PID_Value;
  int speedKanan = baseSpeed - PID_Value;

  gerakMotor(speedKiri, speedKanan);
}

void cekRintanganDepan() {
  float jarakDepan = bacaJarak(TRIG_DEPAN, ECHO_DEPAN);
  if (jarakDepan > 0 && jarakDepan < 12.0) { 
    currentState = AVOID_MANEUVER;
  }
}

// ================= STATE: WALL FOLLOWER =================
void jalankanPIDWallFollower() {
  float jarakKiri = bacaJarak(TRIG_KIRI, ECHO_KIRI);

  // Jika mencapai sudut kotak -> Bypass PID belok kiri tajam mengitari kotak
  if (jarakKiri > 15.0 && jarakKiri < 60.0) {
    gerakMotor(baseSpeed / 4, baseSpeed); 
    lastError_Wall = 0; 
    return;
  }

  float error = targetJarakDinding - jarakKiri; 
  float P = error;
  I_Wall = I_Wall + error;
  float D = error - lastError_Wall;
  
  float PID_Value = (Kp_Wall * P) + (Ki_Wall * I_Wall) + (Kd_Wall * D);
  lastError_Wall = error;

  int speedKiri = baseSpeed - PID_Value;
  int speedKanan = baseSpeed + PID_Value;

  gerakMotor(speedKiri, speedKanan);
}

void cekKembaliKeGaris() {
  // Jika SALAH SATU sensor mendeteksi garis hitam saat memutari dinding
  if (digitalRead(SENSOR_KIRI) || digitalRead(SENSOR_KANAN)) {
    gerakMotor(0, 0); delay(200);
    
    // Putar perlahan ke Kiri (karena tadi memutar kotak ke kanan)
    // Berhenti memutar saat KEDUA sensor berada di area Putih (mengapit garis lagi)
    // ATAU salah satu menyentuh hitam (PID yang akan merapikan nanti)
    while (digitalRead(SENSOR_KIRI) == LOW && digitalRead(SENSOR_KANAN) == LOW) { 
      gerakMotor(-baseSpeed + 40, baseSpeed - 40); 
    }
    
    gerakMotor(0, 0); delay(200);
    
    // Reset memori PID Line agar tidak bergetar hebat saat pertama kali jalan
    lastError_Line = 0; I_Line = 0; 
    currentState = LINE_FOLLOWER; 
  }
}