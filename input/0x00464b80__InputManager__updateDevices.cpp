// FUNC_NAME: InputManager::updateDevices
void InputManager::updateDevices() {
    // Slot size: 0x168 per player (360 bytes)
    // Device data: 0x44 per controller (68 bytes)
    // Array of controllers starts at gDeviceManagerBase + 0x2c
    extern void* gDeviceManagerBase; // DAT_012233b4

    for (int slotIndex = 0; slotIndex <= 15; ++slotIndex) { // 0..15 inclusive, 16 slots
        int slotOffset = slotIndex * 0x168;
        void* deviceData = nullptr;

        // Determine device data pointer for this slot
        if (slotIndex == 0x11) { // Special slot for keyboard/any device (unreachable in 0..15 loop)
            deviceData = static_cast<char*>(gDeviceManagerBase) + 0x2c;
        } else if (slotIndex < 0x10) {
            deviceData = static_cast<char*>(gDeviceManagerBase) + 0x2c + slotIndex * 0x44;
        } else {
            deviceData = nullptr; // Slot 16+ not supported
        }

        // Flags at +0x10 in the slot: non-zero if controller is assigned
        if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slotOffset + 0x10) == 0) {
            goto clearSlot;
        }

        char deviceConnected = 0;
        if (slotIndex < 0x10) {
            // Byte at +0x174: indicates device is connected/active
            deviceConnected = *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + slotOffset + 0x174);
        } else if (slotIndex == 0x11) {
            // Special slot: check all 16 devices; if any is disconnected, treat as disconnected
            deviceConnected = 1;
            for (int i = 0; i < 16; ++i) {
                if (*reinterpret_cast<char*>(reinterpret_cast<char*>(this) + i * 0x168 + 0x174) == 0) {
                    deviceConnected = 0;
                    break;
                }
            }
        } else {
            goto clearSlot; // Unknown slot index -> clear
        }

        if (deviceConnected == 0) {
            goto clearSlot;
        }

        // Device is connected
        if (deviceData == nullptr) {
            // No device data pointer, set a flag that device is missing
            *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x18b8) = 1;
            goto clearSlot;
        }

        // Process the device: call internal functions
        FUN_004663a0(slotIndex);        // Possibly starts device polling
        *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + 0x18b8) = 0; // Clear missing device flag
        FUN_00464dd0(deviceData, slotIndex); // Update device state from this slot

        // Copy input state from device's current state to slot's previous state
        // Slot +0x170 points to a structure containing source data pointer
        // Slot +0x16c points to a structure containing destination data pointer
        int** sourceDesc = *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + slotOffset + 0x170);
        int** destDesc = reinterpret_cast<int**>(reinterpret_cast<char*>(this) + slotOffset + 0x16c);
        int* src = reinterpret_cast<int*>(*sourceDesc);
        int* dst = reinterpret_cast<int*>(*destDesc);
        unsigned short copySize = static_cast<unsigned short>(sourceDesc[2]); // In header at +0x08
        for (unsigned short i = 0; i < copySize; ++i) {
            *reinterpret_cast<char*>(reinterpret_cast<char*>(src) + i) = 
                *reinterpret_cast<char*>(reinterpret_cast<char*>(dst) + i);
        }

        // Final update after copying
        FUN_004651f0(this, slotIndex);

        continue;

clearSlot:
        // Clear the slot's state arrays
        // Offsets: 0x1738, 0x16b8, 0x1838, 0x17b8, 0x173c, 0x16bc, 0x183c, 0x17bc (each 8-byte aligned pairs)
        int* clearTargets[] = {
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1738)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x16b8)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x1838)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17b8)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x173c)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x16bc)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x183c)[slotIndex * 2],
            &reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x17bc)[slotIndex * 2]
        };
        for (int* ptr : clearTargets) {
            *ptr = 0;
        }

        // Zero out specific flags/state within the slot
        *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + slotOffset + 0x47) = 0;
        *reinterpret_cast<char*>(reinterpret_cast<char*>(this) + slotOffset + 0x5f) = 0;
        *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slotOffset + 0x168) = 0;

        // Clear a block of 16 ints starting at offset +0x68 (this covers offsets 0x68 to 0xA7)
        // Using a sliding window, but we simplify to memset for clarity
        for (int i = 0; i < 16; ++i) {
            reinterpret_cast<int*>(reinterpret_cast<char*>(this) + slotOffset + 0x68)[i] = 0;
        }
    }
}