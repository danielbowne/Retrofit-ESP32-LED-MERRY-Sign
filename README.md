# Retrofit MERRY LED Sign Project

![MERRY Sign Retrofit](images/merry.png "Original MERRY Sign before retrofit")

## Overview
This project modernizes a classic battery-powered Christmas MERRY sign through a complete LED retrofit. The original sign, which used traditional Christmas lights, has been upgraded with WS2812 addressable LEDs controlled by an ESP32 microcontroller. This modernization preserves the nostalgic charm of the original sign while adding dynamic lighting capabilities and improved energy efficiency.

The retrofit involves 50 LEDs distributed across the five letters, replacing the original static bulbs with programmable LEDs capable of creating various lighting effects and animations. Each letter maintains its original form factor while gaining the ability to display multiple colors and patterns:
- M: 13 LEDs (positions 0-12)
- E: 10 LEDs (positions 13-22)
- R: 10 LEDs (positions 23-32)
- R: 10 LEDs (positions 33-42)
- Y: 7 LEDs (positions 43-49)

This upgrade transforms a traditional holiday decoration into an interactive, programmable display while maintaining the classic MERRY sign aesthetic.

## Hardware Requirements
- [ESP32 Development Board (ESP-WROOM-32)](https://www.amazon.com/ESP-WROOM-32-Development-Microcontroller-Integrated-Compatible/dp/B08D5ZD528)
- [WS2812 LED Strip](https://www.amazon.com/gp/product/B01AU6UG70/) (50 LEDs, individually addressable)
- 5V Power Supply (adequate for 50 LEDs)
- USB Cable for programming
- Data wire connecting GPIO 5 to LED strip

Notes:
- The LED strip linked is flexible and waterproof, perfect for retrofitting old signs
- Any ESP32 development board will work, I went with these ESP-WROOM-32s because they were a good price and came with expansion board so I can drive it with any adapter 5v-12v

## Software Dependencies
- PlatformIO IDE (Optional, can use Arduino IDE)
- Adafruit NeoPixel Library (`adafruit/Adafruit NeoPixel@^1.12.3`)

## Project Structure
```
MERRY_Sign/
├── src/
│   ├── main.cpp         # Main project code
│   └── config.h         # Configuration file
├── images/
│   └── merry.png        # Project images
├── platformio.ini       # PlatformIO configuration
└── README.md           # This file
```

## Features
The project includes several lighting effects:
1. **Letter Sequence**: Lights up each letter in sequence (M -> E -> R -> R -> Y)
2. **Rainbow Effect**: Each letter cycles through different colors independently
3. **Chase Effect**: A light chase pattern moving through the letters
4. **Twinkle Effect**: Random letters twinkle in white

## Installation
1. Clone this repository
2. Open the project in PlatformIO or Arduino IDE
3. Install required libraries (Adafruit NeoPixel)
4. Connect your ESP32 via USB
5. Upload the code to your board

## Configuration
Key parameters can be adjusted in the `config.h` file:
- `LED_PIN`: GPIO pin for data (default: 5)
- `BRIGHTNESS`: Overall brightness (0-255, default: 50)
- Effect timing parameters for each animation
- Scene duration and transition times

## Hardware Setup
1. Connect the LED strip's data input to GPIO 5
2. Connect the LED strip's power to 5V
3. Connect the LED strip's ground to GND
4. Ensure adequate power supply for all LEDs

## Contributing
Feel free to fork this project and submit improvements or additional effects through pull requests.

## License
This project is open source and available under the MIT License.

## Troubleshooting
- If LEDs don't light up, check power connections
- If colors are wrong, verify the LED type (NEO_GRB + NEO_KHZ800)
- If some LEDs don't work, verify the LED count matches your setup