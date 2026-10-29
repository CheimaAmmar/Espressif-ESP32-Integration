# UART wiring notes

This page is for **ESP32-WROOM-32** or equivalent classic ESP32 modules. Confirm exact pinout and module variant before wiring.

| ESP32 signal | USB-to-UART / external circuit |
| --- | --- |
| 3V3 | Stable regulated 3.3 V supply (not a 5 V output) |
| GND | Shared ground with UART adapter |
| U0TXD / GPIO1 | UART adapter RX (3.3 V logic) |
| U0RXD / GPIO3 | UART adapter TX (3.3 V logic) |
| EN | Pull up to 3.3 V; momentarily pull LOW to reset |
| GPIO0 | Pull up to 3.3 V; hold LOW during reset to enter UART download mode |

Additional ESP32 strapping pins must be in valid startup states. TX/RX are crossed. The 3.3 V supply should support the ESP32's peak Wi-Fi current requirements; many UART adapters' 3.3 V outputs cannot.

## Manual flashing sequence

1. Hold BOOT (GPIO0 LOW).
2. Pulse RESET (EN LOW, then release HIGH).
3. Release BOOT.
4. Upload the firmware via the UART serial port.
5. Restart normally (GPIO0 HIGH) to run the application.

## Green LED observation

The project author reports a green LED that illuminates on the prototype. A lit LED may be a **power indicator** or an application-controlled status LED; without the schematic/GPIO mapping, we cannot determine which. The included firmware does not toggle an LED pin.
