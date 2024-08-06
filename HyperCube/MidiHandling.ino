CHSV channelColor[NUM_CHANNELS];    //initialize (.s) to 255 for all channels... in setup?
boolean noteIsOn[NUM_CHANNELS][42];   //127-85 :: 0-41 for notes 86-127
byte noteBrightness[NUM_CHANNELS][42];//127-85 :: 0-41 for notes 86-127
float channelFade[NUM_CHANNELS];      //Aftertouch to fade brightness up/down per channel
int frame[NUM_CHANNELS][42];

//==============================================================================================================
void setChannelColor(byte channel, byte note, byte velocity) {
  channelColor[channel].h = note*3;
  noteBrightness[channel][note-86] = map(velocity, 1, 127, 0, 255); //uhhhh what??
}
//==============================================================================================================
void handleControlChange(byte channel, byte cntrlNumber, byte cntrlValue) {
    channel--;    //0-indexing :: Library returns 1-16
    if(cntrlNumber == 1)  //modulation wheel --- desaturates to max
    {
      channelColor[channel].s = map(cntrlValue, 0, 127, 255, 0);
      return;
    }
    return;
}
//-----------------------------------------------------------------------
void handleAfterTouch(byte channel, byte velocity) {
  channel--;    //0-indexing :: Library returns 1-16
  channelFade[channel] = (float)velocity/127.0;
  return;
}
//-----------------------------------------------------------------------
void handleNoteOn(byte channel, byte note, byte velocity) {
  channel--;  //0-indexing :: Library returns 1-16
  if(note < 86) {
    setChannelColor(channel, note, velocity);
    return;
  } else {
    noteIsOn[channel][note-86] = true;
    frame[channel][note-86] = 1;
    noteBrightness[channel][note-86] = map(velocity, 1, 127, 0, 255);
    return;
  }
}
//-----------------------------------------------------------------------
void handleNoteOff(byte channel, byte note, byte velocity) {
  channel--;  //0-indexing :: Library returns 1-16
  if(note < 86) {
    return;
  } else {
    noteIsOn[channel][note-86] = false;
    noteBrightness[channel][note-86] = 0;
    frame[channel][note-86] = 0;
    return;
  }
}
//==============================================================================================================
