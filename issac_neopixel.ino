#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6 
#define NUMPIXELS 12

// the Division Orange RGB
byte red = 179;
byte green = 59;
byte blue = 0;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 150 // Time (in milliseconds) to pause between pixels
#define INTERVAL 20000L
#define BLINK_TIMES 3

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  spinLight();
}


void loop() {
  static unsigned long lastSpin = 0;
    static int count = 0;

    unsigned long now = millis();

    if(count > 0) {
        count -= spinTimer();
        lastSpin = now;
    } else {
        if(now - lastSpin >= INTERVAL) {
            count = BLINK_TIMES;
        }
    }
 }

 int spinTimer()
{
  static unsigned long lastFlip = 0;
  static int count = 0;
  bool last = false;

  unsigned long now = millis();

  if(now - lastFlip >= 500) {
    spinLight();
    lastFlip = now;
    count++;
    if (count == 2) {
      count = 0;
      last = true;
      }
   }

   return (last) ? 1 : 0 ;
}

  void spinLight() {
    pixels.clear(); // Set all pixel colors to 'off'
    for(int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      pixels.show();   // Send the updated pixel colors to the hardware.
      delay(DELAYVAL); // Pause before next pass through loop
  }
}
