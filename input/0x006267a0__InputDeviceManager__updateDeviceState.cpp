// FUNC_NAME: InputDeviceManager::updateDeviceState
// Reconstructed from 0x006267a0 - Handles device type detection and input mapping lists
// Based on EA EARS engine input system for The Godfather 2

void __thiscall InputDeviceManager::updateDeviceState(InputDeviceManager *this, DeviceState *device) {
    bool isKeyboard = false;
    bool isVibration = false; // 'v' likely stands for vibration/controller

    // Check if device is active or needs initialization
    if ((*(byte *)(*(int *)(device + 8) + 5) & 0x11) == 0) {
        processDeviceLookup(); // Possibly activates the device
    }

    // Check device type flag (bit 3 of byte at offset 6 in device+8 structure)
    if ((*(byte *)(*(int *)(device + 8) + 6) & 8) == 0) {
        // Get current device configuration (returns two pointers as 64-bit)
        __int64 config = getCurrentDeviceConfig();
        int *lowPtr = (int *)config;
        if (*lowPtr == 0) {
            // Set flag in high pointer's structure to indicate keyboard/controller detection needed
            byte *highByte = (byte *)((int)(config >> 32) + 6);
            *highByte |= 8;
            lowPtr = nullptr;
        }
    } else {
        lowPtr = nullptr;
    }

    // If we have a valid config and it's a device binding (type 4)
    if (lowPtr != nullptr && *lowPtr == 4) {
        // Look for 'k' (keyboard) or 'v' (vibration/controller) in the device name string
        char *name = (char *)(lowPtr[1] + 0x10);
        isKeyboard = _strchr(name, 'k') != nullptr;  // 0x6b
        isVibration = _strchr(name, 'v') != nullptr; // 0x76

        if (isKeyboard || isVibration) {
            // Set device type bits: bit1=keyboard, bit2=controller
            byte newFlags = (byte)((isVibration ? 2 : 0) | (isKeyboard ? 1 : 0)) << 1; // 0x02 factor
            *(byte *)(device + 5) = (*(byte *)(device + 5) & 0xf9) | newFlags;

            // Insert device into the appropriate list in the InputDeviceManager
            int **headPtr;
            if (isKeyboard) {
                if (isVibration) {
                    headPtr = (int **)(this + 0xc); // list for combo devices
                } else {
                    headPtr = (int **)(this + 4);   // keyboard list
                }
            } else {
                headPtr = (int **)(this + 8);       // controller list
            }
            // Store previous head in device->listPrev (offset 0x18)
            *(int *)(device + 0x18) = *headPtr;
            *headPtr = device;

            // If both keyboard and controller, skip the subsequent loops
            if (isVibration) goto skipChildProcessing;
        }
    }

    // Process child bindings stored at device+0xc (8-byte entries)
    int bindingCount = *(int *)(device + 0x1c);
    for (int i = 0; i < bindingCount; i++) {
        int *entry = (int *)(*(int *)(device + 0xc) + i * 8);
        int actionId = *entry;
        if (actionId > 3) {
            int *actionPtr = (int *)entry[1]; // second dword of entry
            if ((*(byte *)(actionPtr + 5) & 0x11) == 0) {
                processDeviceLookup();
            }
        }
    }

skipChildProcessing:
    // Process action mappings at device+0x10 (20-byte entries, count from bitmask)
    int mappingCount = 1 << (*(byte *)(device + 7) & 0x1f);
    if (mappingCount != 0) {
        int stride = mappingCount * 0x14;
        do {
            stride -= 0x14;
            int *mapping = (int *)(*(int *)(device + 0x10) + stride);
            if (mapping[2] != 0) {
                // Check source action
                if (mapping[0] > 3 && (*(byte *)(mapping[1] + 5) & 0x11) == 0 && !isKeyboard) {
                    processDeviceLookup();
                }
                // Check target action
                if (mapping[2] > 3 && (*(byte *)(mapping[3] + 5) & 0x11) == 0 && !isVibration) {
                    processDeviceLookup();
                }
            }
            mappingCount--;
        } while (mappingCount != 0);
    }
}