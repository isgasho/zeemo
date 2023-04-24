import time
import usb_midi
import adafruit_midi
from adafruit_midi.control_change import ControlChange

from machine import Pin, PWM

# LUA CODE FOR UNPACKING
# function unpack_14bit_to_7bit(num)
#   local highBits = num >> 7 -- shift right by 7 bits to get the high bits
#   local lowBits = num & 0x7F -- bitwise AND with 0x7F (01111111 in binary) to get the low bits
#   return lowBits, highBits
# end
# print(split14BitNumber(10389))
# 21, 81

def pack_7bit_to_14bit(tup) :
    return ((tup[1]<<7)|tup[0])
# print(pack_7bit_to_14bit((21,81)))
# 10389

# setup PWMs
pwms=[]
for i, pin in enumerate([6,7,8,9,10,11,12,13]):
    pwms.append(PWM(pin))
    # set to low freq, to allow best resolution
    # https://www.i-programmer.info/programming/hardware/14751-the-pico-in-micropython-pwm.html
    pwms[i].freq(1000)  
     # set to 50% duty on start 
    pwms[i].duty_u16(32768)


midi = adafruit_midi.MIDI(midi_in=usb_midi.ports[0])
while True:
    time.sleep(0.05)
    msg = midi.receive()
    if msg is not None:
        print("Received:", msg, "at", time.monotonic())
        # check midi CC



