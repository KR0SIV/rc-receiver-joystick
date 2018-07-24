/ *
Connector for RC to USB receiver
Emulate Joystick HID to use the 2-channel transmitter in RC simulators

Requirements:
Digispark plate with ATTINY85
Patch to use different interrupts in non-USB IO pins https://github.com/J-Rios/Digispark_DigiUSB-SoftSerial
Perform a jumper between pins 2 and 3 of digispark to enable the USB device
Doubts? www.patolin.com/receptor-rc-digispark
* /


#include <SoftRcPulseIn.h> // reading without pulse block PPM
#include <TinyPinChange.h> // required for SoftRcPulseIn.h
#include "DigiJoystick.h" // HID Digispark Joystick Library

// pins used in the digispark
#define CHANNEL1_PIN 0
#define CHANNEL2_PIN 1
#define CHANNEL3_PIN 5 // optional for 3-channel transmitter

// Create the SoftRcpulseInOut objects to read the PPM pulses
SoftRcPulseIn Channel_1_Pulse;
SoftRcPulseIn Channel_2_Pulse;
SoftRcPulseIn Channel_3_Pulse;

// Transmitter position values
byte chan1val;
byte chan2val;
byte chan3val;


void setup ()
{
  // we assign each pin to its corresponding reading object
  Channel_1_Pulse.attach (CHANNEL1_PIN);
  Channel_2_Pulse.attach (CHANNEL2_PIN);
  Channel_3_Pulse.attach (CHANNEL3_PIN);
}

void loop ()
{
  // we perform a mapping of values, to adjust the PPM range (1000-2000ms) to one byte of data for the joystick (0-255)
  chan1val = map (Channel_1_Pulse.width_us (), 700, 2300, 0, 255);
  chan2val = map (Channel_2_Pulse.width_us (), 700, 2300, 0, 255);
  chan3val = map (Channel_3_Pulse.width_us (), 700, 2300, 0, 255);

  // assign the values ​​to the joystick
  DigiJoystick.setX ((byte) (chan1val));
  DigiJoystick.setY ((byte) (chan2val));
  DigiJoystick.setXROT ((byte) (chan3val));

  // update the joystick values
  DigiJoystick.delay (10); // 10ms delay required by the USB library
}
