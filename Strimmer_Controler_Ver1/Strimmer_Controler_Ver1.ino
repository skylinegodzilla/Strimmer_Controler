#include <Adafruit_NeoPixel.h>


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(26, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(26, 9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripC = Adafruit_NeoPixel(26, 10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripD = Adafruit_NeoPixel(26, 11, NEO_GRB + NEO_KHZ800);

int ledLength = 26;

uint32_t colA = stripA.Color(  255/2,162/2,50/2);
uint32_t colB = stripA.Color(  0,   0, 127);
int offset = 0;

Adafruit_NeoPixel strips [4] = {stripA,stripB,stripC,stripD};

void setup() {
  
   //for (Adafruit_NeoPixel strip : strips){
    //strip.begin();
    //strip.setBrightness(255); //adjust brightness here
    //strip.show(); // Initialize all pixels to 'off'
   //}
   /*
    * Having an issue of using Adafruit_Neo objects in an array. 
    * that is why the above part is commented out
    * Still trying to work out why so for now I have to use this in a cringey way :(  
    *Edit: Turns out that you cant use Adafruit_Neo objects in an array and iliterate 
    *through them without having it crash on 3rd party bords. So ill have to leave the code this way for node MCU's so sad TnT
   */
  
  stripA.begin();
  stripA.setBrightness(255); //adjust brightness here
  stripA.show(); // Initialize all pixels to 'off'
  stripB.begin();
  stripB.setBrightness(255); //adjust brightness here
  stripB.show(); // Initialize all pixels to 'off'
  stripC.begin();
  stripC.setBrightness(255); //adjust brightness here
  stripC.show(); // Initialize all pixels to 'off'
  stripD.begin();
  stripD.setBrightness(255); //adjust brightness here
  stripD.show(); // Initialize all pixels to 'off'
}

void loop() {
    midSplit(20, 30,45,40); //speed, length of the tail, offset for the tails to have time to scroll out, delay between the tales apparing
    theaterChase(50);
  }

//Split of lights down the strips
void midSplit(uint8_t wait, int tailLength, int tailOffset, int sideDelay) {
  for(int j=0; j<10;j++){
      for (int i=0; i < ledLength+tailLength+tailOffset; i++) {
        stripA.setPixelColor(sideDelay+tailLength+(ledLength-tailLength)-i, colB);    //turn every x pixel on
        stripB.setPixelColor(i, colA    );
        stripC.setPixelColor(i, colB);    
        stripD.setPixelColor(sideDelay+tailLength+(ledLength-tailLength)-i, colB);    
        stripA.setPixelColor(sideDelay+tailLength*2+(ledLength-tailLength)-i, 0);    //turn every x pixel off
        stripB.setPixelColor(i-tailLength, 0);    //turn every x pixel off
        stripC.setPixelColor(i-tailLength, 0);    //turn every x pixel off
        stripD.setPixelColor(sideDelay+tailLength*2+(ledLength-tailLength)-i, 0);   
        stripA.show();
        stripB.show();
        stripC.show();
        stripD.show();
        delay(wait);
      }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint8_t wait) {
  for (int j=0; j<40; j++) {  //do x cycles of chasing
    for (int q=0; q < 10; q++) {
      for (int i=0; i < ledLength+20; i=i+10) {
        stripA.setPixelColor(i+q, colB);    //turn every x pixel on
        stripB.setPixelColor(i+1-q, colA);
        stripC.setPixelColor(i+2-q, colB);    
        stripD.setPixelColor(i+3+q, colB);    
      }
      stripA.show();
      stripB.show();
      stripC.show();
      stripD.show();
     
      delay(wait);
     
      for (int i=0; i < ledLength+20; i=i+10) {
        stripA.setPixelColor(i+q, 0);    //turn every x pixel off
        stripB.setPixelColor(i+1-q, 0);   
        stripC.setPixelColor(i+2-q, 0);   
        stripD.setPixelColor(i+3+q, 0);    
      }
    }
  }
}
