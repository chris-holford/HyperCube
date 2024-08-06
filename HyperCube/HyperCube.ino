#include <FastLED.h>
#define NUM_LEDS_PER_STRIP 11
#define NUM_STRIPS_PER_FACE 4
#define NUM_LEDS_PER_FACE (NUM_LEDS_PER_STRIP * NUM_STRIPS_PER_FACE)
#define NUM_FACES 6
#define NUM_SIDES 6
#define NUM_EDGES 12
#define NUM_LEDS (NUM_LEDS_PER_FACE * NUM_FACES)
#define FRAME_TIME 10 //10ms -> 100fps
#define NUM_CHANNELS 16

CRGB leds[NUM_LEDS];
CHSV workArray[NUM_CHANNELS][NUM_LEDS];

//==============================================================================================================
void setStripPixel(int channel, int faceNumber, int stripNumber, int pixel, CHSV color) {
  if(pixel >= NUM_LEDS_PER_STRIP || pixel < 0){return;}
  workArray[channel][pixel + (NUM_LEDS_PER_STRIP *(stripNumber-1)) + (NUM_LEDS_PER_FACE *(faceNumber-1))] = color;
}
//---------------------------------------------------------------------------------
void setStripSolid(int channel, int faceNumber, int stripNumber, CHSV color) {
  for(int i=0; i<NUM_LEDS_PER_STRIP; i++) {
    setStripPixel(channel, faceNumber, stripNumber, i, color);
  }
}
//---------------------------------------------------------------------------------
void setFaceSolid(int channel, int faceNumber, CHSV color) {
  for(int i=1; i<=NUM_STRIPS_PER_FACE; i++) {
    setStripSolid(channel, faceNumber, i, color);
  } 
}
//---------------------------------------------------------------------------------
void setEdgeSolid(int channel, int edgeNumber, CHSV color) {
  switch(edgeNumber) {
    case 1:
        setStripSolid(channel, 1, 3, color);
        setStripSolid(channel, 5, 3, color);
        break;
    case 2:
        setStripSolid(channel, 3, 2, color);
        setStripSolid(channel, 5, 2, color);
        break;
    case 3:
        setStripSolid(channel, 4, 4, color);
        setStripSolid(channel, 5, 1, color);
        break;
    case 4:
        setStripSolid(channel, 5, 4, color);
        setStripSolid(channel, 6, 1, color);
        break;
    case 5:
        setStripSolid(channel, 1, 2, color);
        setStripSolid(channel, 6, 2, color);
        break;
    case 6:
        setStripSolid(channel, 1, 4, color);
        setStripSolid(channel, 3, 1, color);
        break;
    case 7:
        setStripSolid(channel, 3, 3, color);
        setStripSolid(channel, 4, 3, color);
        break;
    case 8:
        setStripSolid(channel, 4, 1, color);
        setStripSolid(channel, 6, 4, color);
        break;
    case 9:
        setStripSolid(channel, 2, 3, color);
        setStripSolid(channel, 6, 3, color);
        break;
    case 10:
        setStripSolid(channel, 1, 1, color);
        setStripSolid(channel, 2, 4, color);
        break;
    case 11:
        setStripSolid(channel, 2, 1, color);
        setStripSolid(channel, 3, 4, color);
        break;
    case 12:
        setStripSolid(channel, 2, 2, color);
        setStripSolid(channel, 4, 2, color);
        break;
    default:
        return;
  }
}
//---------------------------------------------------------------------------------
void setColumnsSolid(int channel, int orientation, CHSV color) {
  switch(orientation) {
    case 1:
        for(int i=5; i<9; i++) {
          setEdgeSolid(channel, i, color);
        }
        break;
    case 2:
        setEdgeSolid(channel, 2, color);
        setEdgeSolid(channel, 4, color);
        setEdgeSolid(channel, 9, color);
        setEdgeSolid(channel, 11, color);
        break;
    case 3:
        setEdgeSolid(channel, 1, color);
        setEdgeSolid(channel, 3, color);
        setEdgeSolid(channel, 10, color);
        setEdgeSolid(channel, 12, color);
        break;
    default:
        break;
  }
  
}
//---------------------------------------------------------------------------------
void setSideSolid(int channel, int sideNumber, CHSV color) {
  switch(sideNumber) {
    case 1:
        setEdgeSolid(channel, 1, color);
        setEdgeSolid(channel, 5, color);
        setEdgeSolid(channel, 6, color);
        setEdgeSolid(channel, 10, color);
        break;
    case 2:
        setEdgeSolid(channel, 9, color);
        setEdgeSolid(channel, 10, color);
        setEdgeSolid(channel, 11, color);
        setEdgeSolid(channel, 12, color);
        break;
    case 3:
        setEdgeSolid(channel, 2, color);
        setEdgeSolid(channel, 6, color);
        setEdgeSolid(channel, 7, color);
        setEdgeSolid(channel, 11, color);
        break;
    case 4:
        setEdgeSolid(channel, 3, color);
        setEdgeSolid(channel, 7, color);
        setEdgeSolid(channel, 8, color);
        setEdgeSolid(channel, 12, color);
        break;
    case 5:
        setEdgeSolid(channel, 1, color);
        setEdgeSolid(channel, 2, color);
        setEdgeSolid(channel, 3, color);
        setEdgeSolid(channel, 4, color);
        break;
    case 6:
        setEdgeSolid(channel, 4, color);
        setEdgeSolid(channel, 5, color);
        setEdgeSolid(channel, 8, color);
        setEdgeSolid(channel, 9, color);
        break;
  }
}
//---------------------------------------------------------------------------------
void clearAll() {
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    for(int j=0; j<NUM_CHANNELS; j++) {
      workArray[j][i].v = 0;
    }
  }
}
//---------------------------------------------------------------------------------
  boolean isReverse[NUM_FACES][NUM_STRIPS_PER_FACE] = {{true,true,false,false},
                                                       {false,true,true,false},
                                                       {true,false,false,true},
                                                       {false,false,true,true},
                                                       {false,true,true,false},
                                                       {true,false,false,true}};
                                                     
int normalizePixelDirection(int faceNumber, int stripNumber, int pixel) {
  if(isReverse[faceNumber-1][stripNumber-1]) {
    pixel = 10 - pixel;
  }
  return pixel;
}
//---------------------------------------------------------------------------------
void setEdgePixel(int channel, int edgeNumber, int pixel, CHSV color) {
  switch(edgeNumber) {
    case 1:
        setStripPixel(channel, 1, 3, normalizePixelDirection(1,3,pixel), color);
        setStripPixel(channel, 5, 3, normalizePixelDirection(5,3,pixel), color);
        break;
    case 2:
        setStripPixel(channel, 3, 2, normalizePixelDirection(3,2,pixel), color);
        setStripPixel(channel, 5, 2, normalizePixelDirection(5,2,pixel), color);
        break;
    case 3:
        setStripPixel(channel, 4, 4, normalizePixelDirection(4,4,pixel), color);
        setStripPixel(channel, 5, 1, normalizePixelDirection(5,1,pixel), color);
        break;
    case 4:
        setStripPixel(channel, 5, 4, normalizePixelDirection(5,4,pixel), color);
        setStripPixel(channel, 6, 1, normalizePixelDirection(6,1,pixel), color);
        break;
    case 5:
        setStripPixel(channel, 1, 2, normalizePixelDirection(1,2,pixel), color);
        setStripPixel(channel, 6, 2, normalizePixelDirection(6,2,pixel), color);
        break;
    case 6:
        setStripPixel(channel, 1, 4, normalizePixelDirection(1,4,pixel), color);
        setStripPixel(channel, 3, 1, normalizePixelDirection(3,1,pixel), color);
        break;
    case 7:
        setStripPixel(channel, 3, 3, normalizePixelDirection(3,3,pixel), color);
        setStripPixel(channel, 4, 3, normalizePixelDirection(4,3,pixel), color);
        break;
    case 8:
        setStripPixel(channel, 4, 1, normalizePixelDirection(4,1,pixel), color);
        setStripPixel(channel, 6, 4, normalizePixelDirection(6,4,pixel), color);
        break;
    case 9:
        setStripPixel(channel, 2, 3, normalizePixelDirection(2,3,pixel), color);
        setStripPixel(channel, 6, 3, normalizePixelDirection(6,3,pixel), color);
        break;
    case 10:
        setStripPixel(channel, 1, 1, normalizePixelDirection(1,1,pixel), color);
        setStripPixel(channel, 2, 4, normalizePixelDirection(2,4,pixel), color);
        break;
    case 11:
        setStripPixel(channel, 2, 1, normalizePixelDirection(2,1,pixel), color);
        setStripPixel(channel, 3, 4, normalizePixelDirection(3,4,pixel), color);
        break;
    case 12:
        setStripPixel(channel, 2, 2, normalizePixelDirection(2,2,pixel), color);
        setStripPixel(channel, 4, 2, normalizePixelDirection(4,2,pixel), color);
        break;
    default:
        return;
  }
}
//==============================================================================================================
