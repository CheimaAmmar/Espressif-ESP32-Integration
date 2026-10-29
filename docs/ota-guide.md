# UART-to-OTA firmware workflow

## Requirements

- Classic ESP32 module powered from a regulated 3.3 V source.
- Arduino IDE with Espressif ESP32 board package installed.
- UART adapter using 3.3 V logic for the first flash.
- Wi-Fi network available to the ESP32 and development computer.
- A flash partition scheme that includes OTA support.

## 1. Flash initial OTA firmware over UART

Open `firmware/esp32_ota/esp32_ota.ino`, set your Wi-Fi credentials and OTA password **locally**, and flash through the UART serial port.

With the serial monitor set to **115200 baud**, look for:

```text
Connected! IP address: <device-local-IP>
OTA is ready for updates over the local Wi-Fi network.
```

These lines illustrate expected output; they are not captured logs from the project.

## 2. Update to example v1.1 over Wi-Fi

Open `firmware/ota_v2/ota_v2.ino`, set the same Wi-Fi credentials and OTA password locally, and choose the ESP32's OTA network port in Arduino IDE. Upload over the local network.

The updated sketch should show on restart:

```text
Firmware version: 1.1.0
```

Seeing this output after a network upload demonstrates the version change. A green LED remaining on does not establish which firmware is running.

The OTA target port may fail to appear if mDNS discovery is blocked. Confirm that both devices are on the appropriate local network, check firewall settings, and verify the serial output and IP address. If OTA cannot be restored, use UART for recovery.

## 3. Troubleshooting

| Symptom | Check |
| --- | --- |
| UART `Failed to connect` | BOOT/RESET sequence, TX↔RX wiring, 3.3 V logic, shared GND |
| Reboots or Wi-Fi instability | Regulated 3.3 V supply and enough peak current |
| No OTA network port | Wi-Fi connection, mDNS discovery, firewall and computer network |
| OTA password error | Password match and current sketch configuration |
| OTA upload fails | OTA partition scheme and available flash space |
| OTA lost after a new firmware | Updated sketch still starts OTA and calls `ArduinoOTA.handle()` |

## Security

This demonstration is for a trusted local network. Do not expose ArduinoOTA directly to the internet or publish real credentials in the repository. For production, consider verified firmware images and robust rollback/recovery handling.
