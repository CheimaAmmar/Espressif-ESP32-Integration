# Project test record

This record distinguishes observations **reported by the project author** from tests not independently documented in this repository. No screenshot or serial log has been fabricated.

| Test | Current record | Evidence / notes |
| --- | --- | --- |
| Prototype assembled and powered | Reported working | Author reports all basic functions working |
| Green LED | Reported ON | Function of LED (power/status/GPIO) not yet identified |
| Initial UART firmware upload | Reported working | Actual command/serial log not attached |
| Wi-Fi connection & OTA functionality | Reported working | Actual logs/screenshots not attached |
| OTA example v1.1 upload | Example provided; not documented as tested | Verify by checking `Firmware version: 1.1.0` after a Wi-Fi update |
| Automatic Wi-Fi reconnection in v1.1 | Code provided; not documented as tested | Disconnect/reconnect AP and log behavior |

## Optional manual verification (no screenshots required)

1. Record the date, ESP32 module variant and Arduino IDE / core version used.
2. From a 115200 baud Serial Monitor session, copy **non-sensitive** lines showing IP assigned and OTA ready.
3. Perform an OTA update from v1 to v1.1 and record the success message.
4. Restart the ESP32 and record the `Firmware version: 1.1.0` line.
5. Note whether the green LED is a power indicator or is connected to a specific GPIO. Do not claim an LED blink test until confirmed.

Never include Wi-Fi passwords, OTA passwords, or private network details in public evidence.
