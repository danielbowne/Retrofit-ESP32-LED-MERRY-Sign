#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Function declarations (prototypes)
void setLetterColor(int startLed, int length, uint32_t color);
void clearStrip();
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
  // Run different letter-based effects
  letterSequence(EffectConfig::SEQUENCE_LETTER_DURATION);
  delay(SCENE_TRANSITION);
  
  letterRainbow(EffectConfig::RAINBOW_CYCLES);
  delay(SCENE_TRANSITION);
  
  letterChase(COLOR_RED, EffectConfig::CHASE_SPEED, EffectConfig::CHASE_CYCLES);
  delay(SCENE_TRANSITION);
  
  letterTwinkle(EffectConfig::TWINKLE_DURATION, EffectConfig::TWINKLE_CYCLES);
  delay(SCENE_TRANSITION);
}

// Helper function to clear all LEDs
void clearStrip() {
  for(int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, COLOR_OFF);
  }
}

// Helper function to set color for a specific letter
void setLetterColor(int startLed, int length, uint32_t color) {
  for(int i = startLed; i < startLed + length; i++) {
    strip.setPixelColor(i, color);
  }
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

// Effect 2: Rainbow effect per letter
void letterRainbow(int cycles) {
  unsigned long effectStart = millis();
  int c = 0;
  
  while (millis() - effectStart < SCENE_DURATION) {
    uint32_t m_color = strip.ColorHSV((c * 65536 / cycles) % 65536);
    uint32_t e_color = strip.ColorHSV(((c * 65536 / cycles) + 13107) % 65536);
    uint32_t r1_color = strip.ColorHSV(((c * 65536 / cycles) + 26214) % 65536);
    uint32_t r2_color = strip.ColorHSV(((c * 65536 / cycles) + 39321) % 65536);
    uint32_t y_color = strip.ColorHSV(((c * 65536 / cycles) + 52428) % 65536);
    
    if (USE_GAMMA_CORRECTION) {
      m_color = strip.gamma32(m_color);
      e_color = strip.gamma32(e_color);
      r1_color = strip.gamma32(r1_color);
      r2_color = strip.gamma32(r2_color);
      y_color = strip.gamma32(y_color);
    }
    
    setLetterColor(M_START, M_LENGTH, m_color);
    setLetterColor(E1_START, E1_LENGTH, e_color);
    setLetterColor(R1_START, R1_LENGTH, r1_color);
    setLetterColor(R2_START, R2_LENGTH, r2_color);
    setLetterColor(Y_START, Y_LENGTH, y_color);
    
    strip.show();
    delay(EffectConfig::RAINBOW_SPEED);
    c++;
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

// Effect 4: Twinkle effect per letter
void letterTwinkle(int wait, int cycles) {
  unsigned long effectStart = millis();
  
  while (millis() - effectStart < SCENE_DURATION) {
    // Pick a random letter to twinkle
    int letter = random(5);
    int startLed, length;
    
    switch(letter) {
      case 0: startLed = M_START; length = M_LENGTH; break;
      case 1: startLed = E1_START; length = E1_LENGTH; break;
      case 2: startLed = R1_START; length = R1_LENGTH; break;
      case 3: startLed = R2_START; length = R2_LENGTH; break;
      case 4: startLed = Y_START; length = Y_LENGTH; break;
    }
    
    // Twinkle the chosen letter
    setLetterColor(startLed, length, COLOR_WHITE);
    strip.show();
    delay(wait);
    setLetterColor(startLed, length, COLOR_OFF);
    strip.show();
    delay(wait/2);
  }
}