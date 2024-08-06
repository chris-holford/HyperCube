//12 edge Ons
//6 side On
//6 face On
//3 column +orientation(0, 1, 2)
//1 wholeCube solid
//13 chasers (1-13)
//This is channel-specific (channel info is passed to all functions)
//Writes to channel workArray[NUM_LEDS]
//0-41 indexed scan for ...IsOn(midNotes 86-127)

//==============================================================================================================
void drawChannelArrays() {  //"overload" to pass all channels
  for(byte i=0; i<NUM_CHANNELS; i++) {
    drawChannelArray(i);
  }
}
//-----------------------------------------------------------------------
void drawChannelArray(byte channel) {
  for(int i=0; i<42; i++) {
    if(noteIsOn[channel][i]) {
      byte adjustedBrightness = noteBrightness[channel][i] * channelFade[channel];
      CHSV color = CHSV(channelColor[channel].h, channelColor[channel].s, adjustedBrightness);
      if(i<1) {
        for(int j=0; j<NUM_LEDS; j++) {
          workArray[channel][j].v = 0;
        }
        return;
      } else if(i<2) {
        for(int j=0; j<NUM_LEDS; j++) {
          workArray[channel][j] = color;
        }
        return;
      } else if(i<14) {
        setEdgeSolid(channel, (i-1), color);//set edge 1-12
      } else if(i<20) { 
        setSideSolid(channel, (i-13), color);//set side 1-6
      } else if(i<23) { 
        setColumnsSolid(channel, (i-19), color);//set Orientation 1-3
      } else if(i<29) { 
        setFaceSolid(channel, (i-22), color);//set face 1-6
      } else {
        int chaser = i-28;
        switch(chaser) {
          case 1:
            chaser1(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 2:
            chaser2(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 3:
            chaser3(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 4:
            chaser4(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 5:
            chaser5(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 6:
            chaser6(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 7:
            chaser7(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 8:
            chaser8(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 9:
            chaser9(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 10:
            chaser10(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 11:
            chaser11(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 12:
            chaser12(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          case 13:
            chaser13(channel, color, frame[channel][i]);
            frame[channel][i]++;
            break;
          default:
            break;
        }
      }
    }
  }
}
//==============================================================================================================
void sumChannelArrays() { //hmmmm.....
  for(int i=0; i<NUM_CHANNELS; i++) {
    for(int j=0; j<NUM_LEDS ; j++) {
      leds[j] += workArray[i][j];
    }
  }
}
//==============================================================================================================
