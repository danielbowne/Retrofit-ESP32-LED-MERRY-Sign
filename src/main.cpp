#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Function declarations (prototypes)
void setLetterColor(int startLed, int length, uint32_t color);
void clearStrip();
void fadeInAndHold();  // Added new function prototype
void letterSequence(int wait);
void letterRainbow(int cycles);
void letterChase(uint32_t color, int wait, int cycles);
void letterTwinkle(int wait, int cycles);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  // Start with fade in and hold
  fadeInAndHold();
  delay(SCENE_TRANSITION);
  
  // Run existing letter-based effects
  letterSequence(EffectConfig::SEQUENCE_LETTER_DURATION);
  delay(SCENE_TRANSITION);
   
  letterChase(COLOR_RED, EffectConfig::CHASE_SPEED, EffectConfig::CHASE_CYCLES);
  delay(SCENE_TRANSITION);
  
  letterTwinkle(EffectConfig::TWINKLE_DURATION, EffectConfig::TWINKLE_CYCLES);
  delay(SCENE_TRANSITION);
}

// Helper Functions
void clearStrip() {
  for(int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, COLOR_OFF);
  }
}

void setLetterColor(int startLed, int length, uint32_t color) {
  for(int i = startLed; i < startLed + length; i++) {
    strip.setPixelColor(i, color);
  }
}

// Effect Functions
// Effect 0: Slow fade from off to bright white, then hold
void fadeInAndHold() {
  const unsigned long FADE_DURATION = 5000;    // 5 seconds for the fade
  const unsigned long HOLD_DURATION = 60000;   // 60 seconds hold time
  unsigned long effectStart = millis();
  
  // First phase: Fade in
  while (millis() - effectStart < FADE_DURATION) {
    float progress = (float)(millis() - effectStart) / FADE_DURATION;
    uint8_t brightness = progress * 255;  // Calculate current brightness level
    
    // Set all LEDs to white at current brightness
    for(int i = 0; i < LED_COUNT; i++) {
      // Warm white: More red, slightly less blue
      strip.setPixelColor(i, strip.Color(brightness, brightness * 0.95, brightness * 0.8));
    }
    
    strip.show();
    delay(20);  // Small delay for smooth transition
  }
  
  // Second phase: Hold at full brightness
  for(int i = 0; i < LED_COUNT; i++) {
    // Warm white: Full red, 95% green, 80% blue
    strip.setPixelColor(i, strip.Color(255, 242, 204));
  }
  strip.show();
  
  // Hold for the remaining time
  delay(HOLD_DURATION);
}

// Effect 1: Light up letters in sequence
void letterSequence(int wait) {
  unsigned long effectStart = millis();
  
  while (millis() - effectStart < SCENE_DURATION) {
    clearStrip();
    strip.show();
    
    // M
    setLetterColor(M_START, M_LENGTH, COLOR_RED);
    strip.show();
    delay(wait);
    
    // E
    setLetterColor(E1_START, E1_LENGTH, COLOR_GREEN);
    strip.show();
    delay(wait);
    
    // R
    setLetterColor(R1_START, R1_LENGTH, COLOR_RED);
    strip.show();
    delay(wait);
    
    // R
    setLetterColor(R2_START, R2_LENGTH, COLOR_GREEN);
    strip.show();
    delay(wait);
    
    // Y
    setLetterColor(Y_START, Y_LENGTH, COLOR_RED);
    strip.show();
    delay(wait);
  }
}

// Effect 3: Chase effect through letters
void letterChase(uint32_t color, int wait, int cycles) {
  unsigned long effectStart = millis();
  
  while (millis() - effectStart < SCENE_DURATION) {
    // Chase forward
    for(int letter = 0; letter < 5; letter++) {
      clearStrip();
      switch(letter) {
        case 0: setLetterColor(M_START, M_LENGTH, color); break;
        case 1: setLetterColor(E1_START, E1_LENGTH, color); break;
        case 2: setLetterColor(R1_START, R1_LENGTH, color); break;
        case 3: setLetterColor(R2_START, R2_LENGTH, color); break;
        case 4: setLetterColor(Y_START, Y_LENGTH, color); break;
      }
      strip.show();
      delay(wait);
    }
    
    // Chase backward
    for(int letter = 4; letter >= 0; letter--) {
      clearStrip();
      switch(letter) {
        case 0: setLetterColor(M_START, M_LENGTH, color); break;
        case 1: setLetterColor(E1_START, E1_LENGTH, color); break;
        case 2: setLetterColor(R1_START, R1_LENGTH, color); break;
        case 3: setLetterColor(R2_START, R2_LENGTH, color); break;
        case 4: setLetterColor(Y_START, Y_LENGTH, color); break;
      }
      strip.show();
      delay(wait);
    }
  }
}

// Effect 4: Camera flash effect with random LEDs
void letterTwinkle(int wait, int cycles) {
  unsigned long effectStart = millis();
  
  // Track flash state for each LED
  bool ledFlashing[LED_COUNT] = {false};  // Initialize all to false
  unsigned long flashStartTime[LED_COUNT] = {0};
  const int FLASH_DURATION = 50;  // Duration of each flash in milliseconds
  const int NUM_SIMULTANEOUS_FLASHES = 5;  // How many LEDs can flash at once
  
  while (millis() - effectStart < SCENE_DURATION) {
    unsigned long currentTime = millis();
    
    // Count current flashing LEDs
    int flashingCount = 0;
    for(int i = 0; i < LED_COUNT; i++) {
      if(ledFlashing[i]) flashingCount++;
    }
    
    // Try to start new flashes if we're below the simultaneous flash limit
    while(flashingCount < NUM_SIMULTANEOUS_FLASHES) {
      int ledIndex = random(LED_COUNT);  // Pick a random LED
      
      // If this LED isn't already flashing, start it
      if(!ledFlashing[ledIndex]) {
        ledFlashing[ledIndex] = true;
        flashStartTime[ledIndex] = currentTime;
        flashingCount++;
      }
    }
    
    // Update all LEDs
    for(int i = 0; i < LED_COUNT; i++) {
      // Check if flash should end
      if(ledFlashing[i] && (currentTime - flashStartTime[i] > FLASH_DURATION)) {
        ledFlashing[i] = false;
      }
      
      // Set LED color based on flash state
      if(ledFlashing[i]) {
        strip.setPixelColor(i, COLOR_WHITE);  // Bright flash
      } else {
        strip.setPixelColor(i, COLOR_OFF);    // Off between flashes
      }
    }
    
    strip.show();
    delay(10);  // Quick update for sharp flashes
  }
}