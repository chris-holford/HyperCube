void setup() {
  
    FastLED.addLeds<NUM_FACES, WS2812, 19, GRB>(leds, NUM_LEDS_PER_FACE).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(255);
    FastLED.clear(true);
    //--------------------------
    usbMIDI.begin();
    usbMIDI.setHandleNoteOn(handleNoteOn);
    usbMIDI.setHandleNoteOff(handleNoteOff);
    usbMIDI.setHandleControlChange(handleControlChange);
    usbMIDI.setHandleAfterTouch(handleAfterTouch);
    //--------------------------
    for(int i=0; i<NUM_CHANNELS; i++) { 
      channelColor[i].s = 255;          //default all channels to full saturation before mod wheel info
      channelFade[i] = 1;               //set channelFades to full bright
    }
}
//==============================================================================================================
void loop() {
  usbMIDI.read(); //everything executed in callbacks; animationOn/data updated "real-time"
  EVERY_N_MILLISECONDS(FRAME_TIME) {
    clearAll();           //clear the .show() array
    drawChannelArrays();  //stage the work arrays
    sumChannelArrays();   //push channel(s) data to .show() array
    FastLED.show();
  }
}
