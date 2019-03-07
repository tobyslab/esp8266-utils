/*
    Simple FeatherWing NeoPixel Rainbow Demo
    By Toby Boreham
    2019-02-28
    main.cpp

    To do:
    Make wipe in and out programatic
 */

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#define T 0                     // Transparent
#define R 1                     // Red
#define Y 2                     // Yellow
#define G 3                     // Green
#define B 4                     // Blue
#define V 5                     // Violet
#define RGB_RED        0        // RGB red value
#define RGB_GREEN      1        // RGB red value
#define RGB_BLUE       2        // RGB red value
#define DISPLAY_WIDTH  4        // Number of pixels wide
#define INVERT_DISPLAY          // Invert the display
#define INTENSITY      1        // Intensity multiplier (1 - 255)

// NeoPixel pin
#define PIN            15

// Number of NeoPixels
#define NUMPIXELS      32

// Delay between frames
#define FRAME_DELAY 100

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Function prototypes
void setup(void);
void loop(void);
void rainbow(void);

// Run once
void setup() {
  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
}

// Main loop
void loop() {
  rainbow();
}

// Rainbow function
void rainbow() {
    static const int rainbow[8][24] = {
            { T, T, T, T, T, T, T, T, T, R, R, R, R, R, R, T, T, T, T, T, T, T, T, T },
            { T, T, T, T, T, T, T, R, R, Y, Y, Y, Y, Y, Y, R, R, T, T, T, T, T, T, T },
            { T, T, T, T, T, T, R, Y, Y, G, G, G, G, G, G, Y, Y, R, T, T, T, T, T, T },
            { T, T, T, T, T, R, Y, G, G, B, B, B, B, B, B, G, G, Y, R, T, T, T, T, T },
            { T, T, T, T, T, R, Y, G, B, V, V, V, V, V, V, B, G, Y, R, T, T, T, T, T },
            { T, T, T, T, R, Y, G, B, V, V, T, T, T, T, V, V, B, G, Y, R, T, T, T, T },
            { T, T, T, T, R, Y, G, B, V, T, T, T, T, T, T, V, B, G, Y, R, T, T, T, T },
            { T, T, T, T, R, Y, G, B, V, T, T, T, T, T, T, V, B, G, Y, R, T, T, T, T } };

#ifndef INVERT_DISPLAY
    static const int ledMap[8][4] = {
            { 24, 16, 8, 0 },
            { 25, 17, 9, 1 },
            { 26, 18, 10, 2 },
            { 27, 19, 11, 3 },
            { 28, 20, 12, 4 },
            { 29, 21, 13, 5 },
            { 30, 22, 14, 6 },
            { 31, 23, 15, 7 } };
#endif
#ifdef INVERT_DISPLAY
    static const int ledMap[8][4] = {
            { 7, 15, 23, 31 },
            { 6, 14, 22, 30 },
            { 5, 13, 21, 29 },
            { 4, 12, 20, 28 },
            { 3, 11, 19, 27 },
            { 2, 10, 18, 26 },
            { 1, 9, 17, 25 },
            { 0, 8, 16, 24 } };
#endif

    static const int color[6][3] = {
            { 0x00, 0x00, 0x00 },                         // Transparent RGB
            { 0x01, 0x00, 0x00 },                         // Red RGB
            { 0x01, 0x01, 0x00 },                         // Yellow RGB
            { 0x00, 0x01, 0x00 },                         // Green RGB
            { 0x00, 0x00, 0x01 },                         // Blue RGB
            { 0x01, 0x00, 0x01 } };                       // Violet RGB 

    for(int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            for(int k = 0; k < DISPLAY_WIDTH; k++) {
                pixels.setPixelColor(ledMap[j][k], 
                    color[rainbow[j][i + k]][RGB_RED] * INTENSITY, 
                    color[rainbow[j][i + k]][RGB_GREEN] * INTENSITY, 
                    color[rainbow[j][i + k]][RGB_BLUE] * INTENSITY);
            }
            pixels.show();
        }
        delay(FRAME_DELAY);
    }
}
