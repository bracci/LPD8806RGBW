#ifndef LPD8806RGBW_H
#define LPD8806RGBW_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

class LPD8806RGBW {

 public:

  LPD8806RGBW(uint16_t n, uint8_t dpin, uint8_t cpin); // Configurable pins
  LPD8806RGBW(uint16_t n); // Use SPI hardware; specific pins only
  LPD8806RGBW(void); // Empty constructor; init pins & strip length later
  void
    begin(void),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0),
    setPixelColor(uint16_t n, uint32_t c),
    show(void),
    updatePins(uint8_t dpin, uint8_t cpin), // Change pins, configurable
    updatePins(void),                       // Change pins, hardware SPI
    updateLength(uint16_t n);               // Change strip length
  uint16_t
    numPixels(void);
  uint32_t
    Color(byte r, byte g, byte b, byte w = 0),
    getPixelColor(uint16_t n);

 private:

  uint16_t
    numLEDs,    // Number of RGB LEDs in strip
    numBytes;   // Size of 'pixels' buffer below
  uint8_t
    *pixels,    // Holds LED color values (6 bytes each) + 2 latch bytes
    clkpin    , datapin;     // Clock & data pin numbers
#ifdef __AVR__
  uint8_t
    clkpinmask, datapinmask; // Clock & data PORT bitmasks
  volatile uint8_t
    *clkport  , *dataport;   // Clock & data PORT registers
#endif
  void
    startBitbang(void),
    startSPI(void);
  boolean
    hardwareSPI, // If 'true', using hardware SPI
    begun;       // If 'true', begin() method was previously invoked
};
#endif // LPD8806_H