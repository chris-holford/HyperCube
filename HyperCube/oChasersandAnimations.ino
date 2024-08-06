// functions accept channel, color, and frame
//write to channel workArray
//chaser1()-chaser13()
//...other animations?

//==============================================================================================================
  CHSVPalette16 chaser1Palette;
  #define COOLING 80
  #define SPARKING 50
void chaser1(byte channel, CHSV color, int frame) { //Palette Fire
  if((frame%3) != 0) { return;}   //slow it down to every n frame
  chaser1Palette = CHSVPalette16(CHSV(color.h-30,255,0), 
                                 color,
                                 CHSV(color.h+30, 150, color.v-20));
  static byte heat[NUM_LEDS_PER_STRIP];
    //Fire! no framing needed
//    random16_add_entropy( random());
    //Step 1 --- Cool everything down
    for( int j=0; j<NUM_LEDS_PER_STRIP; j++) {
      heat[j] = qsub8( heat[j],  random8(0, ((COOLING * 10) / NUM_LEDS_PER_STRIP) + 2));
    }
    // Step 2 --- diffuse heat up
    if((frame%6) == 0) {
      for( int k=NUM_LEDS_PER_STRIP - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
      }
    }
    // Step 3 --- Random ignition
//    if( random8() < SPARKING ) {
//      int y = random8(3);
//      heat[y] = qadd8( heat[y], random8(120,200) );
//    }
    if((frame%15) == 0) {
      heat[0] = qadd8(heat[0], random(100,240));
    } else if ((frame%9) == 0) {
      heat[1] = qadd8(heat[1], random(100,240));
    }
    // Step 4 -- Map heat to color palette
    for( int j=0; j<NUM_LEDS_PER_STRIP; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8(heat[j], 240);
      CHSV paletteColor = ColorFromPalette(chaser1Palette, colorindex);
      for(int i=5; i<9; i++) {  //edges 5-8
        setEdgePixel(channel, i, j, paletteColor);
      }
    }
}
//-----------------------------------------------------------------------
void chaser2(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser3(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser4(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser5(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser6(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser7(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser8(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser9(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser10(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser11(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser12(byte channel, CHSV color, int frame) {
  
}
//-----------------------------------------------------------------------
void chaser13(byte channel, CHSV color, int frame) {
  
}
//==============================================================================================================
