import os



# Set the LED GPIO pin
LED_PIN2  = 2
LED_PIN3  = 3
LED_PIN4  = 4
LED_PIN17 = 17
LED_PIN27 = 27

# Set the GPIO direction
GPIO_DIRECTION = "out"

# Set the GPIO value
GPIO_VALUE_ON = "1"
GPIO_VALUE_OFF = "0"


# Function to turn on the LED
def led_on(LED_PIN):
    with open(f"/sys/class/gpio/gpio{LED_PIN}/value", "w") as f:
        f.write(GPIO_VALUE_ON)

# Function to turn off the LED
def led_off(LED_PIN):
    with open(f"/sys/class/gpio/gpio{LED_PIN}/value", "w") as f:
        f.write(GPIO_VALUE_OFF)


def set_gpio_pin(PIN):
    if not os.path.exists(f"/sys/class/gpio/gpio{PIN}"):
        with open("/sys/class/gpio/export", "w") as f:
            f.write(str(PIN))
        with open(f"/sys/class/gpio/gpio{PIN}/direction", "w") as f:
            f.write(GPIO_DIRECTION)



