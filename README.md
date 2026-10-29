# Espressif ESP32 Integration — UART Flashing & OTA

Standalone **Espressif ESP32-WROOM-32** module programming via **USB-to-UART** and **Over-the-Air (OTA)** updates using the Arduino ESP32 core.

This repository documents a compact ESP32 prototype and its firmware.

## Project overview

A development board provides built-in USB and support circuitry, but a standalone ESP32 module can be integrated into a compact embedded device with a suitable external power and programming circuit.

The workflow is:

1. Wire the ESP32 and a **3.3 V logic** USB-to-UART adapter.
2. Flash the first OTA-capable firmware through UART.
3. Connect the device to Wi-Fi.
4. Upload a later firmware revision over Wi-Fi while preserving OTA support.

## Prototype photo

![Standalone ESP32 prototype](images/esp32.png)

## Hardware wiring

| ESP32 pin | Connection | Purpose |
| --- | --- | --- |
| 3V3 | Regulated 3.3 V supply | Power |
| GND | Common supply and USB-to-UART ground | Ground reference |
| GPIO1 / U0TXD | USB-to-UART RX | ESP32 transmit |
| GPIO3 / U0RXD | USB-to-UART TX | ESP32 receive |
| EN | Pull-up to 3.3 V; RESET switch to GND | Enable / reset |
| GPIO0 | Pull-up to 3.3 V; BOOT switch to GND | Select UART download mode |

**Electrical safety:** Never connect 5 V directly to the ESP32's 3V3 or GPIO pins. Use an adequately rated 3.3 V supply, and verify bootstrapping pins and the pinout of the exact module. See [wiring notes](docs/wiring.md).

**Green LED:** The assembled prototype's green LED was reported to turn on. This shows an observable indicator is lit; it does *not* by itself prove Wi-Fi/OTA success or establish which GPIO, if any, controls it. The firmware examples do not assume an LED pin.

## Repository contents

```text
Espressif-ESP32-Integration/
├── README.md
├── .gitignore
├── images/
│   └── esp32.png
├── firmware/
│   ├── esp32_ota/
│   │   └── esp32_ota.ino       # Initial UART firmware (v1)
│   └── ota_v2/
│       └── ota_v2.ino          # Optional OTA update example (v1.1)
└── docs/
    ├── wiring.md
    ├── ota-guide.md
    └── test-results.md
```

## First UART upload

1. Install [Arduino IDE](https://www.arduino.cc/en/software/) and the **Espressif ESP32** board package.
2. Open [`firmware/esp32_ota/esp32_ota.ino`](firmware/esp32_ota/esp32_ota.ino).
3. Fill in the Wi-Fi and OTA password placeholders.
4. Select a matching ESP32 board target, correct serial port, and a **partition scheme with OTA support**.
5. Enter download mode if required: hold BOOT (GPIO0 LOW), tap RESET (EN LOW then HIGH), release BOOT, then upload over UART.
6. Release BOOT and restart. Open Serial Monitor at **115200 baud** to check the device's Wi-Fi IP and the `OTA is ready` message.

## Upload a second firmware over Wi-Fi

The optional [`firmware/ota_v2/ota_v2.ino`](firmware/ota_v2/ota_v2.ino) example keeps ArduinoOTA active, prints **`Firmware version: 1.1.0`** on startup, and retries Wi-Fi connection if it drops.

1. Keep the ESP32 powered on and connected to the same trusted local network as the computer.
2. Open `ota_v2.ino` in Arduino IDE and set the **same Wi-Fi credentials and OTA password used for v1**.
3. Select an OTA-capable partition scheme and the ESP32's network port in Arduino IDE; ensure mDNS and firewall settings allow discovery.
4. Upload via the network port and supply the OTA password when prompted.
5. After the restart, check **Serial Monitor at 115200 baud** for the `Firmware version: 1.1.0` message to confirm that this *particular* update was applied.
   
See the [OTA procedure and troubleshooting](docs/ota-guide.md).

## Tests and Status

The ESP32 hardware prototype has been successfully assembled, programmed, and tested.

The following functionalities have been validated:

- **Hardware Integration:** The standalone ESP32 module is powered and operational.
- **Green LED:** The green LED turns ON successfully during testing.
- **UART Programming:** The initial firmware has been successfully uploaded through the USB-to-UART interface.
- **Wi-Fi Connectivity:** The ESP32 successfully connects to the wireless network.
- **OTA Programming:** Wireless firmware updates have been successfully performed without requiring a physical USB connection.

The project is fully functional for its initial objectives. An additional OTA firmware version (v2) is included for future improvements and testing.

Detailed test results are available in [`docs/test-results.md`](docs/test-results.md).

## Security notes

- Use a strong OTA password and a trusted local network; do not expose the ArduinoOTA service to the public internet.
- Keep an accessible UART connection for recovery if OTA stops working.

## References

- [ESP32-WROOM-32 datasheet](https://documentation.espressif.com/esp32-wroom-32_datasheet_en.html)
- [Arduino-ESP32 documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [ArduinoOTA BasicOTA example](https://github.com/espressif/arduino-esp32/blob/master/libraries/ArduinoOTA/examples/BasicOTA/BasicOTA.ino)
- [ESP32 OTA partitions](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/ota.html)
