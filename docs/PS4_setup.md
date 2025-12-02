# PS4 (DualShock 4) setup and usage

This project supports PS4 controllers via the `aed3/PS4-esp32` library. Below are the basic steps and tips for pairing and testing with the ESP32 dev board.

Pairing notes
- If your PS4 controller is currently paired to a PS4 console, you'll need to either unpair it or change the MAC address on the controller. See the original library README for pairing options.
- You can use `PS4.begin()` without parameters to start Bluetooth discovery and accept controller connections if the controller is unpaired.
- If you need to emulate a specific MAC address for pairing, pass a MAC string to `PS4.begin("aa:bb:cc:11:22:33")` in `src/input_ps4.cpp`.

Controls mapping
- D-Pad: moves the snake (UP/DOWN/LEFT/RIGHT)
- Left analog stick: also moves the snake if magnitude beyond a threshold
- Options button: resets the game (edge-detected — press once to reset)

Debugging & verification
- Open the serial monitor (baud rate 115200). When a controller connects you should see `PS4: connected` and direction changes will log `PS4: dir <DIRECTION>`.
- If the controller won’t connect, try unpairing it from any console and use the `sixaxispairer` tool (see library README in case you need to edit the PS4 stored MAC address).

Library
- This project added the PS4 library as a Git dependency in `platformio.ini`:

```
lib_deps = 
  adafruit/Adafruit SSD1306@^2.5.15
  adafruit/Adafruit GFX Library@^1.12.4
  https://github.com/aed3/
  .git
```

If you want to change the mapping or add rumble/LED feedback, the `PS4` global instance is available (see `src/input_ps4.cpp`).
