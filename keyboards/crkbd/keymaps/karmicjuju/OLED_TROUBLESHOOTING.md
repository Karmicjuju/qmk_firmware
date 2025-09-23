# Corne v4.1 OLED Troubleshooting Guide

## Software Fixes Applied

1. **Added I2C Configuration** (config.h)
   - Added I2C driver and pin definitions required for v4.1
   ```c
   #define I2C_DRIVER I2CD1
   #define I2C1_SDA_PIN GP6
   #define I2C1_SCL_PIN GP7
   ```

2. **Fixed OLED Function** (keymap.c)
   - Ensured `oled_task_user()` returns `false`
   - Created simplified test function to verify OLED works

3. **Build Script** (build.sh)
   - Use from QMK root directory: `./keyboards/crkbd/keymaps/karmicjuju/build.sh`
   - Builds specifically for crkbd/rev4_1

## Hardware Troubleshooting Steps

If OLEDs still don't work after flashing the updated firmware:

### 1. Check Physical Connections
- **Inspect OLED pins**: VCC, GND, SDA (GP6), SCL (GP7)
- Look for:
  - Cold solder joints (dull, grainy appearance)
  - Solder bridges between pins
  - Bent or damaged pins
- **Reflow solder** if connections look questionable

### 2. Remove Protective Film
- Many OLED displays ship with protective plastic film
- This film can be nearly invisible but blocks the display
- Carefully peel off any film from the OLED surface

### 3. Test Each Half Separately
1. Disconnect TRRS cable
2. Connect left half via USB
3. Flash firmware to left half
4. Check if OLED displays "OLED TEST"
5. Repeat for right half

### 4. Try Alternative I2C Address
If default address (0x3C) doesn't work, add to config.h:
```c
#define OLED_I2C_ADDRESS 0x3D
```

### 5. Voltage Testing with Multimeter
With keyboard powered on, measure:
- **VCC to GND**: Should read 3.3V
- **SDA to GND**: Should read ~3.3V (may fluctuate during data transmission)
- **SCL to GND**: Should read ~3.3V (may fluctuate during clock signals)

### 6. Test with Different OLED Module
- If available, swap OLED modules to determine if hardware is faulty
- SSD1306 128x64 OLED modules are standard for Corne

### 7. Check for v4.1 Known Issues
- v4.1 has reported issues with left half not working correctly
- Some users report electromagnetic interference from phones
- Try moving away from electronic devices during testing

## Flashing Instructions for RP2040 (v4.1)

1. **Enter bootloader mode**:
   - Hold BOOT button while connecting USB, OR
   - While connected, hold BOOT and tap RESET

2. **RPI-RP2 drive appears**

3. **Copy firmware**:
   - Drag `.build/crkbd_rev4_1_karmicjuju.uf2` to the drive
   - Drive will disconnect automatically

4. **Repeat for other half**

## Restoring Original OLED Function

Once OLED is confirmed working with test function:
1. Edit keymap.c
2. Remove the simplified test function
3. Uncomment the original function (currently in comment block)
4. Rebuild and reflash

## Additional Resources

- [QMK OLED Driver Docs](https://docs.qmk.fm/features/oled_driver)
- [SplitKB OLED Troubleshooting](https://docs.splitkb.com/troubleshooting/oled-display)
- [Corne Build Guide](https://github.com/foostan/crkbd/blob/main/docs/firmware/rev4/firmware_en.md)