#ifndef CONFIG_H
#define CONFIG_H

// Pin and LED configuration
#define LED_PIN         5       // GPIO pin connected to the LED strip
#define LED_COUNT      50      // Total number of LEDs
#define BRIGHTNESS     50      // Default brightness (0-255)

// Letter definitions
#define M_START        0       // M starts at LED 0
#define M_LENGTH      13      // M has 13 LEDs
#define E1_START      13      // First E starts at LED 13
#define E1_LENGTH     10      // First E has 10 LEDs
#define R1_START      23      // First R starts at LED 23
#define R1_LENGTH     10      // First R has 10 LEDs
#define R2_START      33      // Second R starts at LED 33
#define R2_LENGTH     10      // Second R has 10 LEDs
#define Y_START       43      // Y starts at LED 43
#define Y_LENGTH       7      // Y has 7 LEDs

// Scene timing configuration (all times in milliseconds)
#define SCENE_DURATION        3000    // How long each scene runs
#define SCENE_TRANSITION      1000    // Delay between scenes

// Individual effect configurations
struct EffectConfig {
    // Letter Sequence effect
    static const int SEQUENCE_LETTER_DURATION = 100;  // Time each letter stays lit

    // Rainbow effect
    static const int RAINBOW_CYCLES = 20;            // Number of color cycles
    static const int RAINBOW_SPEED = 50;             // Delay between color changes

    // Chase effect
    static const int CHASE_SPEED = 50;              // Speed of the chase movement
    static const int CHASE_CYCLES = 3;              // Number of complete chases

    // Twinkle effect
    static const int TWINKLE_DURATION = 100;        // How long each twinkle lasts
    static const int TWINKLE_CYCLES = 2;            // Number of twinkle cycles
};

// Color presets (in RGB format)
#define COLOR_RED       0xFF0000    // Red
#define COLOR_GREEN     0x00FF00    // Green
#define COLOR_BLUE      0x0000FF    // Blue
#define COLOR_WHITE     0xFFFFFF    // White
#define COLOR_GOLD      0xFFD700    // Gold
#define COLOR_OFF       0x000000    // Off/Black

// Advanced settings
#define USE_GAMMA_CORRECTION true   // Enable/disable gamma correction
#define ENABLE_RANDOM_SCENES false  // Randomize scene order instead of sequential

#endif // CONFIG_H