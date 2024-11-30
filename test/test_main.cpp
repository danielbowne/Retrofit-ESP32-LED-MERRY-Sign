#include <unity.h>

// Mock Adafruit_NeoPixel class for testing
class Adafruit_NeoPixel {
public:
    Adafruit_NeoPixel(uint16_t n, uint8_t p, uint8_t t) : num_leds(n), pin(p) {
        pixels = new uint32_t[n];
        brightness = 50;
        for(uint16_t i = 0; i < n; i++) {
            pixels[i] = 0;
        }
    }
    
    void begin() {}
    void show() {}
    void setBrightness(uint8_t b) { brightness = b; }
    
    void setPixelColor(uint16_t n, uint32_t c) {
        if (n < num_leds) pixels[n] = c;
    }
    
    uint32_t getPixelColor(uint16_t n) {
        return (n < num_leds) ? pixels[n] : 0;
    }
    
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
    }
    
    ~Adafruit_NeoPixel() { delete[] pixels; }

private:
    uint16_t num_leds;
    uint8_t pin;
    uint8_t brightness;
    uint32_t* pixels;
};

// LED configuration
#define LED_PIN    5
#define LED_COUNT  50
#define BRIGHTNESS 50

// Letter definitions
#define M_START    0
#define M_LENGTH   13
#define E1_START   13
#define E1_LENGTH  10
#define R1_START   23
#define R1_LENGTH  10
#define R2_START   33
#define R2_LENGTH  10
#define Y_START    43
#define Y_LENGTH   7

// Color definitions
#define COLOR_RED    0xFF0000
#define COLOR_GREEN  0x00FF00
#define COLOR_BLUE   0x0000FF
#define COLOR_WHITE  0xFFFFFF
#define COLOR_GOLD   0xFFD700
#define COLOR_OFF    0x000000

// Global strip object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, 0);

// Function implementations
void setLetterColor(int startLed, int length, uint32_t color) {
    for(int i = startLed; i < startLed + length; i++) {
        strip.setPixelColor(i, color);
    }
}

void clearStrip() {
    for(int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, COLOR_OFF);
    }
}

// Test setup and teardown
void setUp(void) {
    clearStrip();  // Initialize before each test
}

void tearDown(void) {
    clearStrip();  // Clean up after each test
}

// Basic Tests
void test_letter_boundaries(void) {
    TEST_ASSERT_EQUAL(0, M_START);
    TEST_ASSERT_EQUAL(13, M_LENGTH);
    TEST_ASSERT_EQUAL(13, E1_START);
    TEST_ASSERT_EQUAL(10, E1_LENGTH);
    TEST_ASSERT_EQUAL(23, R1_START);
    TEST_ASSERT_EQUAL(10, R1_LENGTH);
    TEST_ASSERT_EQUAL(33, R2_START);
    TEST_ASSERT_EQUAL(10, R2_LENGTH);
    TEST_ASSERT_EQUAL(43, Y_START);
    TEST_ASSERT_EQUAL(7, Y_LENGTH);
    TEST_ASSERT_EQUAL(50, LED_COUNT);
}

void test_set_letter_color(void) {
    // Test setting color for M
    setLetterColor(M_START, M_LENGTH, COLOR_RED);
    for (int i = M_START; i < M_START + M_LENGTH; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_RED, strip.getPixelColor(i));
    }
    
    // Test setting color for Y
    setLetterColor(Y_START, Y_LENGTH, COLOR_GREEN);
    for (int i = Y_START; i < Y_START + Y_LENGTH; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_GREEN, strip.getPixelColor(i));
    }
}

void test_clear_strip(void) {
    // First set some colors
    setLetterColor(M_START, M_LENGTH, COLOR_RED);
    setLetterColor(Y_START, Y_LENGTH, COLOR_GREEN);
    
    // Clear the strip
    clearStrip();
    
    // Verify all LEDs are off
    for (int i = 0; i < LED_COUNT; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_OFF, strip.getPixelColor(i));
    }
}

// Advanced Tests
void test_color_values(void) {
    uint32_t color = strip.Color(255, 128, 64);
    TEST_ASSERT_EQUAL_HEX32(0xFF8040, color);
    
    color = strip.Color(0, 255, 0);
    TEST_ASSERT_EQUAL_HEX32(COLOR_GREEN, color);
    
    color = strip.Color(255, 215, 0);
    TEST_ASSERT_EQUAL_HEX32(COLOR_GOLD, color);
}

void test_letter_sequence_init(void) {
    // Set all LEDs to a color
    for(int i = 0; i < LED_COUNT; i++) {
        strip.setPixelColor(i, COLOR_RED);
    }
    
    clearStrip();
    // Verify all LEDs start off
    for(int i = 0; i < LED_COUNT; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_OFF, strip.getPixelColor(i));
    }
}

void test_letter_bounds_check(void) {
    // Test M letter bounds
    setLetterColor(M_START, M_LENGTH, COLOR_RED);
    // Check the last LED of M and first LED of E
    TEST_ASSERT_EQUAL_HEX32(COLOR_RED, strip.getPixelColor(M_START + M_LENGTH - 1));
    TEST_ASSERT_EQUAL_HEX32(COLOR_OFF, strip.getPixelColor(M_START + M_LENGTH));
    
    clearStrip();
    
    // Test Y letter bounds
    setLetterColor(Y_START, Y_LENGTH, COLOR_GREEN);
    // Check the last LED of R2 and first LED of Y
    TEST_ASSERT_EQUAL_HEX32(COLOR_OFF, strip.getPixelColor(Y_START - 1));
    TEST_ASSERT_EQUAL_HEX32(COLOR_GREEN, strip.getPixelColor(Y_START));
}

void test_multiple_letters(void) {
    // Set alternating colors for all letters
    setLetterColor(M_START, M_LENGTH, COLOR_RED);
    setLetterColor(E1_START, E1_LENGTH, COLOR_GREEN);
    setLetterColor(R1_START, R1_LENGTH, COLOR_BLUE);
    setLetterColor(R2_START, R2_LENGTH, COLOR_RED);
    setLetterColor(Y_START, Y_LENGTH, COLOR_GREEN);
    
    // Verify each letter maintains its color
    for(int i = M_START; i < M_START + M_LENGTH; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_RED, strip.getPixelColor(i));
    }
    
    for(int i = E1_START; i < E1_START + E1_LENGTH; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_GREEN, strip.getPixelColor(i));
    }
    
    for(int i = R1_START; i < R1_START + R1_LENGTH; i++) {
        TEST_ASSERT_EQUAL_HEX32(COLOR_BLUE, strip.getPixelColor(i));
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    // Basic functionality tests
    RUN_TEST(test_letter_boundaries);
    RUN_TEST(test_set_letter_color);
    RUN_TEST(test_clear_strip);
    
    // Advanced functionality tests
    RUN_TEST(test_color_values);
    RUN_TEST(test_letter_sequence_init);
    RUN_TEST(test_letter_bounds_check);
    RUN_TEST(test_multiple_letters);
    
    return UNITY_END();
}