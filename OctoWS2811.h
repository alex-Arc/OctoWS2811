/*  OctoWS2811 - High Performance WS2811 LED Display Library
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef OctoWS2811_h
#define OctoWS2811_h

#ifndef OctoWS2811Version
#define OctoWS2811Version 100020001
#define octo_has_4_channel  // remove when next version commes
#endif

#include <Arduino.h>
#include "DMAChannel.h"

#if TEENSYDUINO < 121
#error "Teensyduino version 1.21 or later is required to compile this library."
#endif
#ifdef __AVR__
#error "OctoWS2811 does not work with Teensy 2.0 or Teensy++ 2.0."
#endif

#define WS2811_RGB	0x0	// The WS2811 datasheet documents this way
#define WS2811_RBG	0x1
#define WS2811_GRB	0x2	// Most LED strips are wired this way
#define WS2811_GBR  0x3
#define WS2811_RGBW	0x4
#define WS2811_RBGW	0x5
#define WS2811_GRBW	0x6
#define WS2811_GBRW	0x7

#define WS2811_800kHz 0x00	// Nearly all WS2811 are 800 kHz
#define WS2811_400kHz 0x10	// Adafruit's Flora Pixels
#define WS2813_800kHz 0x20	// WS2813 are close to 800 kHz but has 300 us frame set delay
#define SK6812_820kHz 0x30


class OctoWS2811 {
public:
	OctoWS2811(uint32_t numPerStrip, void *frameBuf, void *drawBuf, uint8_t config = WS2811_GRB);
	void begin(void);

	void setPixel(uint32_t num, uint32_t color);
	void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue) {
		setPixel(num, color(red, green, blue));
	}

	void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    setPixel(num, color(red, green, blue, white));
	}

	int getPixel(uint32_t num);

	void show(void);
	int busy(void);

	int numPixels(void) {
		return stripLen * 8;
	}
	int color(uint8_t red, uint8_t green, uint8_t blue) {
		return (red << 16) | (green << 8) | blue;
	}

  int color(uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
		return (red << 24) | (green << 16) | (blue << 8) | white;
	}


private:
	static uint16_t stripLen;
	static void *frameBuffer;
	static void *drawBuffer;
	static uint8_t params;
  uint16_t frameSetDelay;
  uint8_t oneLEDbufferSize;
	static DMAChannel dma1, dma2, dma3;
	static void isr(void);
};

#endif
