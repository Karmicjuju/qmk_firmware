#!/bin/bash

# Build script for Corne v4.1 keyboard with OLED support
# Make sure you're in the QMK root directory before running this

echo "Building firmware for Corne v4.1..."
echo "Target keyboard: crkbd/rev4_1"
echo "Keymap: karmicjuju"
echo ""

# Clean previous builds
echo "Cleaning previous builds..."
qmk clean

# Compile the firmware
echo "Compiling firmware..."
qmk compile -kb crkbd/rev4_1 -km karmicjuju

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ Build successful!"
    echo ""
    echo "Firmware file created at:"
    echo ".build/crkbd_rev4_1_karmicjuju.uf2"
    echo ""
    echo "To flash:"
    echo "1. Connect one half while holding the BOOT button"
    echo "2. RPI-RP2 drive should appear"
    echo "3. Copy the .uf2 file to the drive"
    echo "4. Repeat for the other half"
else
    echo ""
    echo "✗ Build failed! Please check the error messages above."
    exit 1
fi