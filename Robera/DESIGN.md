---
name: Tech-Playful Robotics System
colors:
  surface: '#f8f9ff'
  surface-dim: '#ccdbf3'
  surface-bright: '#f8f9ff'
  surface-container-lowest: '#ffffff'
  surface-container-low: '#eff4ff'
  surface-container: '#e6eeff'
  surface-container-high: '#dce9ff'
  surface-container-highest: '#d5e3fc'
  on-surface: '#0d1c2e'
  on-surface-variant: '#434655'
  inverse-surface: '#233144'
  inverse-on-surface: '#eaf1ff'
  outline: '#737686'
  outline-variant: '#c3c6d7'
  surface-tint: '#0053db'
  primary: '#004ac6'
  on-primary: '#ffffff'
  primary-container: '#2563eb'
  on-primary-container: '#eeefff'
  inverse-primary: '#b4c5ff'
  secondary: '#9d4300'
  on-secondary: '#ffffff'
  secondary-container: '#fd761a'
  on-secondary-container: '#5c2400'
  tertiary: '#3a5f00'
  on-tertiary: '#ffffff'
  tertiary-container: '#4c7a00'
  on-tertiary-container: '#d3ff9b'
  error: '#ba1a1a'
  on-error: '#ffffff'
  error-container: '#ffdad6'
  on-error-container: '#93000a'
  primary-fixed: '#dbe1ff'
  primary-fixed-dim: '#b4c5ff'
  on-primary-fixed: '#00174b'
  on-primary-fixed-variant: '#003ea8'
  secondary-fixed: '#ffdbca'
  secondary-fixed-dim: '#ffb690'
  on-secondary-fixed: '#341100'
  on-secondary-fixed-variant: '#783200'
  tertiary-fixed: '#acf847'
  tertiary-fixed-dim: '#91db2a'
  on-tertiary-fixed: '#102000'
  on-tertiary-fixed-variant: '#304f00'
  background: '#f8f9ff'
  on-background: '#0d1c2e'
  surface-variant: '#d5e3fc'
typography:
  headline-xl:
    fontFamily: Rubik
    fontSize: 48px
    fontWeight: '700'
    lineHeight: 56px
    letterSpacing: -0.02em
  headline-lg:
    fontFamily: Rubik
    fontSize: 32px
    fontWeight: '600'
    lineHeight: 40px
  headline-lg-mobile:
    fontFamily: Rubik
    fontSize: 28px
    fontWeight: '600'
    lineHeight: 34px
  headline-md:
    fontFamily: Rubik
    fontSize: 24px
    fontWeight: '600'
    lineHeight: 32px
  body-lg:
    fontFamily: Plus Jakarta Sans
    fontSize: 18px
    fontWeight: '400'
    lineHeight: 28px
  body-md:
    fontFamily: Plus Jakarta Sans
    fontSize: 16px
    fontWeight: '400'
    lineHeight: 24px
  label-md:
    fontFamily: Plus Jakarta Sans
    fontSize: 14px
    fontWeight: '600'
    lineHeight: 20px
    letterSpacing: 0.05em
rounded:
  sm: 0.25rem
  DEFAULT: 0.5rem
  md: 0.75rem
  lg: 1rem
  xl: 1.5rem
  full: 9999px
spacing:
  base: 8px
  gutter: 24px
  margin-mobile: 16px
  margin-desktop: 64px
  container-max: 1280px
---

## Brand & Style
The design system is engineered for the intersection of high-technology and early childhood education. It balances the precision of robotics with the boundless energy of a playground. The brand personality is "The Friendly Inventor": intelligent and systematic, yet approachable and enthusiastic. 

The aesthetic follows a **Tech-Playful** movement. It utilizes clean, modern layouts typical of high-end SaaS, but injects "joyful friction" through oversized rounded corners, vibrant color pops, and subtle technical motifs like circuit-inspired linework. The goal is to make STEM feel like an invitation to play rather than a difficult subject to master.

## Colors
The palette is built on three core "Power-Up" colors and a stable neutral base.

- **Primary (Circuit Blue):** A vibrant, high-energy blue that represents logic, technology, and the digital world.
- **Secondary (Ignition Orange):** A warm, stimulating orange used for "action" moments—starting a lesson, launching a bot, or celebrating success.
- **Tertiary (Bio-Green):** A bright lime green that ties technology back to the real world and sustainability, often used for "Correct" states and growth indicators.
- **Neutrals:** Soft slates and light greys ensure the interface remains readable and doesn't overwhelm the young user's cognitive load.

The background should remain predominantly white or very light grey (`#F8FAFC`) to let the vibrant accents lead the eye.

## Typography
Typography is optimized for legibility and friendliness. We use **Rubik** for all headings; its slightly rounded corners and geometric construction mirror the physical components of robotic kits. 

For body text, **Plus Jakarta Sans** provides a clean, modern feel with high x-heights, making it extremely easy for young readers to parse instructions. 

- Use **Headline-XL** sparingly for hero sections and milestone achievements.
- Use **Label-MD** for technical metadata and small UI descriptors to maintain a sense of "Pro-Tech" organization.

## Layout & Spacing
The layout uses a **Fluid Grid** system based on an 8px rhythmic scale. 

- **Desktop:** 12-column grid with wide 64px margins to create a "contained" and safe feeling for the content.
- **Mobile:** 4-column grid with 16px margins.
- **Rhythm:** Elements should be spaced generously. Use `32px` or `48px` between major sections to prevent the UI from feeling "cramped" or intimidating.

The layout philosophy is "One Task at a Time." Avoid dense sidebars; favor centered content blocks that guide the user through a linear learning path.

## Elevation & Depth
This design system uses **Tonal Layers** combined with **Ambient Shadows** to create a sense of physical play-objects sitting on a surface.

1.  **Level 0 (Base):** The canvas. Usually white or #F8FAFC.
2.  **Level 1 (Cards):** Subtle, soft shadows (0px 4px 20px rgba(0,0,0,0.05)) with a 1px border in a slightly darker neutral to define the boundary.
3.  **Level 2 (Interactive):** When hovered or active, elements should lift slightly with a more pronounced shadow (0px 8px 30px rgba(0,0,0,0.1)).

Avoid heavy black shadows. Use tinted shadows (e.g., a faint blue-tinted shadow for primary buttons) to maintain the vibrant, clean aesthetic.

## Shapes
The shape language is defined by "The Safety Radius." All interactive elements must be rounded to ensure the UI feels soft and non-threatening.

- **Standard Buttons & Inputs:** Use the `0.5rem` (8px) base roundedness.
- **Cards & Educational Modules:** Use `rounded-lg` (16px) to create a distinct, friendly container.
- **Status Pills & Tags:** Use `rounded-xl` (24px) or full pill-shapes to differentiate them from functional buttons.
- **Circuit Graphics:** Any decorative line-art should use rounded caps and joins to match the UI components.

## Components

### Buttons
Primary buttons are high-contrast Blue with white text. Use a subtle "press" effect where the button moves 2px down on click to mimic physical hardware buttons. Secondary buttons use an Orange outline.

### Progress Trackers
Essential for educational motivation. Use the **Tertiary Green** for completed steps. Progress bars should be thick (12px height) with fully rounded ends.

### Cards
Cards are the primary container for lessons. They should feature a top-heavy layout with a colorful illustration or icon, followed by a **Headline-MD** and a clear call-to-action button at the bottom.

### Inputs & Forms
Input fields should have a 2px border in a light neutral color. On focus, the border should change to **Primary Blue** with a soft outer glow. This clear visual feedback is critical for children learning to navigate digital forms.

### Gamification Chips
Small, colorful labels (using the full palette) that highlight "XP," "Levels," or "Skills" (e.g., [Coding], [Mechanics]). These should always have a light background of the color they represent with dark text for high contrast.