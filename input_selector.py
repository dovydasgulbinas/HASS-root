#!/usr/bin/python
import sys
import RPi.GPIO as GPIO ## Import GPIO library
import time

# print('Number of arguments:', len(sys.argv), 'arguments.')
# print('Argument List:', str(sys.argv))

usage = """
arg1 - channel number
arg2 - input gpio pin
arg3 - comma separated list no spaces

python input_selector.py 1 5 16,20,12
"""
print(usage)

channel = int(sys.argv[1])
changer_pin = int(sys.argv[2])
state_pins = map(int, sys.argv[3].split(","))

# state_pins = [16, 20, 21]
# changer_pin = 5
sleep_delay = 0.05
debounce_delay = 0.05

#GPIO.setwarnings(False)

def init_pins():
    GPIO.setmode(GPIO.BCM) ## Use board pin numbering
    GPIO.setup(changer_pin, GPIO.OUT) ## Setup GPIO Pin 5 to OUT

    for pin in state_pins:
        GPIO.setup(pin, GPIO.IN)


def change_source():
    """Assuming that your HW will work on Falling edge """
    print(">>> Changing Source!")
    GPIO.output(changer_pin,True) ## Turn on GPIO pin 5
    time.sleep(sleep_delay)
    GPIO.output(changer_pin,False) ## Turn on GPIO pin 5
    time.sleep(sleep_delay)
    GPIO.output(changer_pin,True) ## Turn on GPIO pin 5

def togle_channel(channel):
    """Channel must range from 1 - 3"""
    selected_pin = state_pins[channel - 1]
    for i in range(1,4):
        state = GPIO.input(selected_pin)
        print("i: {}, state: {}".format(i, state))
        if state:
            print("i: {} pin: {}".format(i, selected_pin))
            return True
        change_source()
        time.sleep(debounce_delay)

    print("Failed to get sate of any of the pins")
    return False

def get_initial_active_pin():
    for pin in state_pins:
        state = GPIO.input(pin)
        if state:
            return state_pins.index(pin) + 1 # returns original channel
    return None


try:
    init_pins()
    initial_state = get_initial_active_pin()

    if not togle_channel(channel): # retun to last state
        if initial_state:
            print("Restoring original state")
            togle_channel(initial_state)
        else:
            print("Did not restore state because all states were off")


except Exception as e:
    print("Some error: {}".format(e))
finally:
    GPIO.cleanup() # this ensures a clean exit

# True False will change channel!
