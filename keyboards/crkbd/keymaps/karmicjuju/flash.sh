#!/bin/bash
# Flash script for Corne v4.1 on Arch Linux

echo "Corne v4.1 Flash Script for Arch Linux"
echo "======================================="
echo ""
echo "1. First, build the firmware:"
echo "   cd /home/karmic/Documents/Git/qmk_firmware"
echo "   qmk compile -kb crkbd/rev4_1/standard -km karmicjuju"
echo ""
echo "2. Put keyboard half into bootloader mode:"
echo "   - Hold BOOT button while connecting USB, OR"
echo "   - While connected, hold BOOT and tap RESET"
echo ""
echo "3. Wait for RPI-RP2 drive to appear..."

# Wait for the RPI-RP2 drive to be mounted
while [ ! -d "/run/media/$USER/RPI-RP2" ] && [ ! -d "/media/RPI-RP2" ] && [ ! -d "/mnt/RPI-RP2" ]; do
    echo -n "."
    sleep 1
done

echo ""
echo "RPI-RP2 drive detected!"

# Find the mount point
if [ -d "/run/media/$USER/RPI-RP2" ]; then
    MOUNT_POINT="/run/media/$USER/RPI-RP2"
elif [ -d "/media/RPI-RP2" ]; then
    MOUNT_POINT="/media/RPI-RP2"
elif [ -d "/mnt/RPI-RP2" ]; then
    MOUNT_POINT="/mnt/RPI-RP2"
else
    echo "Error: Could not find RPI-RP2 mount point"
    exit 1
fi

# Copy the firmware
FW_FILE="/home/karmic/Documents/Git/qmk_firmware/.build/crkbd_rev4_1_standard_karmicjuju.uf2"

if [ -f "$FW_FILE" ]; then
    echo "Copying firmware to $MOUNT_POINT..."
    cp "$FW_FILE" "$MOUNT_POINT/"
    echo "Firmware flashed successfully!"
    echo ""
    echo "The drive will disconnect automatically."
    echo "Repeat for the other half."
else
    echo "Error: Firmware file not found at $FW_FILE"
    echo "Please build the firmware first with:"
    echo "  qmk compile -kb crkbd/rev4_1/standard -km karmicjuju"
    exit 1
fi