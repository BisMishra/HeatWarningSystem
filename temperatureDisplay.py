import sys
from lcd import drivers

display = drivers.Lcd()

try:
    while True: 
        display.lcd_display_string("Temperature: ", 1)
        display.lcd_display_string("Humidity: ", 2)
except KeyboardInterrupt:
    print("Clearning up!")
    display.lcd_clear()