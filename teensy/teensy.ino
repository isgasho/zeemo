/*
   You must select MIDI from the "Tools > USB Type" menu
*/

void setup() {
  Serial.begin(115200);
  Serial.println("MIDI begin3");

  // setup pwm
  // https://www.pjrc.com/teensy/td_pulse.html
  // pinMode(PIN_D0,0);
  for (byte i = 0; i < 8; i++) {
    pinMode(i,OUTPUT);
    analogWriteFrequency(i, 9155);
  }
  analogWriteResolution(14);
  // pinMode(0,OUTPUT);
  // pinMode(1,OUTPUT);
  // analogWrite(0,200);
  // analogWrite(1,200);
}

void loop() {
  // usbMIDI.read() needs to be called rapidly from loop().  When
  // each MIDI messages arrives, it return true.  The message must
  // be fully processed before usbMIDI.read() is called again.
  if (usbMIDI.read()) {
    processMIDI();
  }
}

word map(word x, word in1, word in2, word out1, word out2) {
  return out1 + ((out2 - out1) * (x - in1) / (in2 - in1));
}

void processMIDI(void) {
  Serial.println("GOT MIDI!");
  byte type, channel, data1, data2, cable;

  // fetch the MIDI message, defined by these 5 numbers (except SysEX)
  //
  type = usbMIDI.getType();        // which MIDI message, 128-255
  channel = usbMIDI.getChannel();  // which MIDI channel, 1-16
  data1 = usbMIDI.getData1();      // first data byte of message, 0-127
  data2 = usbMIDI.getData2();      // second data byte of message, 0-127
  cable = usbMIDI.getCable();      // which virtual cable with MIDIx8, 0-7

  // uncomment if using multiple virtual cables
  // Serial.print("cable ");
  // Serial.print(cable, DEC);
  // Serial.print(": ");

  // print info about the message
  //
  switch (type) {
    case usbMIDI.NoteOff:  // 0x80
      Serial.print("Note Off, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case usbMIDI.NoteOn:  // 0x90
      Serial.print("Note On, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case usbMIDI.AfterTouchPoly:  // 0xA0
      Serial.print("AfterTouch Change, ch=");
      Serial.print(channel, DEC);
      Serial.print(", note=");
      Serial.print(data1, DEC);
      Serial.print(", velocity=");
      Serial.println(data2, DEC);
      break;

    case usbMIDI.ControlChange:  // 0xB0
      Serial.print("Control Change, ch=");
      Serial.print(channel, DEC);
      Serial.print(", control=");
      Serial.print(data1, DEC);
      Serial.print(", value=");
      Serial.println(data2, DEC);
      analogWrite(channel - 1, (data1 << 7) | data2);
      Serial.print("writing to channel ");
      Serial.print(channel-1);
      Serial.print(" value ");
      Serial.println( (data1 << 7) | data2 );
      break;

    case usbMIDI.ProgramChange:  // 0xC0
      Serial.print("Program Change, ch=");
      Serial.print(channel, DEC);
      Serial.print(", program=");
      Serial.println(data1, DEC);
      break;

    case usbMIDI.AfterTouchChannel:  // 0xD0
      Serial.print("After Touch, ch=");
      Serial.print(channel, DEC);
      Serial.print(", pressure=");
      Serial.println(data1, DEC);
      break;

    case usbMIDI.PitchBend:  // 0xE0
      Serial.print("Pitch Change, ch=");
      Serial.print(channel, DEC);
      Serial.print(", pitch=");
      Serial.println(data1 + data2 * 128, DEC);
      break;

    case usbMIDI.SystemExclusive:  // 0xF0
      // Messages larger than usbMIDI's internal buffer are truncated.
      // To receive large messages, you *must* use the 3-input function
      // handler.  See InputFunctionsComplete for details.
      Serial.print("SysEx Message: ");
      printBytes(usbMIDI.getSysExArray(), data1 + data2 * 256);
      Serial.println();
      break;

    case usbMIDI.TimeCodeQuarterFrame:  // 0xF1
      Serial.print("TimeCode, index=");
      Serial.print(data1 >> 4, DEC);
      Serial.print(", digit=");
      Serial.println(data1 & 15, DEC);
      break;

    case usbMIDI.SongPosition:  // 0xF2
      Serial.print("Song Position, beat=");
      Serial.println(data1 + data2 * 128);
      break;

    case usbMIDI.SongSelect:  // 0xF3
      Serial.print("Sond Select, song=");
      Serial.println(data1, DEC);
      break;

    case usbMIDI.TuneRequest:  // 0xF6
      Serial.println("Tune Request");
      break;

    case usbMIDI.Clock:  // 0xF8
      Serial.println("Clock");
      break;

    case usbMIDI.Start:  // 0xFA
      Serial.println("Start");
      break;

    case usbMIDI.Continue:  // 0xFB
      Serial.println("Continue");
      break;

    case usbMIDI.Stop:  // 0xFC
      Serial.println("Stop");
      break;

    case usbMIDI.ActiveSensing:  // 0xFE
      Serial.println("Actvice Sensing");
      break;

    case usbMIDI.SystemReset:  // 0xFF
      Serial.println("System Reset");
      break;

    default:
      Serial.println("Opps, an unknown MIDI message type!");
  }
}

void printBytes(const byte *data, unsigned int size) {
  while (size > 0) {
    byte b = *data++;
    if (b < 16) Serial.print('0');
    Serial.print(b, HEX);
    if (size > 1) Serial.print(' ');
    size = size - 1;
  }
}
