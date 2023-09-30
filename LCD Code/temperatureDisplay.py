import Drivers

display = Drivers.Lcd()

try:
    while True: 
        display.lcd_display_string("Temperature: ", 1)
except KeyboardInterrupt:
    print("Clearning up!")
    display.lcd_clear()