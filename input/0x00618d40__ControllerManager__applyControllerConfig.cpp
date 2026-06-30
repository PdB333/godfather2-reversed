// FUNC_NAME: ControllerManager::applyControllerConfig
// Function address: 0x00618d40
// Updates controller slot state based on configuration data from a device profile.
// Compares current stored values with desired values and calls vibration/state set functions if changed.

// Structure for a controller configuration entry (0x38 bytes each)
struct ControllerConfigEntry {
    /* +0x00 */ uint8_t unknown[0x14];   // Padding or other fields
    /* +0x14 */ int32_t deviceType;      // Used in final call (vtable+0x104)
    /* +0x18 */ uint8_t unknown2[0x04];
    /* +0x1c */ uint32_t configIndex;    // Index into global config table (DAT_011a0f28)
    /* +0x20 */ uint8_t leftMotor;       // Vibration motor left
    /* +0x21 */ uint8_t rightMotor;      // Vibration motor right
    /* +0x22 */ uint8_t triggerMotor;    // Trigger vibration
    /* +0x23 */ uint8_t unknownMotor1;   // Possibly another motor
    /* +0x24 */ uint8_t unknownMotor2;   // Set three times (maybe left/right/trigger?)
    /* +0x25 */ uint8_t padding[3];
    /* +0x28 */ int32_t someIntValue;    // Another state value
    /* +0x2c */ uint8_t padding2[0x0C];
};

// Global arrays (size per slot = 0xC bytes)
// DAT_011f7450: array of bytes (slot*0xC + 0)
// DAT_011f7451: array of bytes (slot*0xC + 1)
// DAT_011f7452: array of bytes (slot*0xC + 2)
// DAT_011f7453: array of bytes (slot*0xC + 3)
// DAT_011f7454: array of bytes (slot*0xC + 4)
// DAT_011f7458: array of ints (slot*0xC + 8)

// Global pointers to manager objects with vtables
extern void* DAT_01205750; // Manager object with vtable
extern void* DAT_0120595c; // Another manager object with vtable

// Forward declaration of helper function
bool FUN_00618c40(void); // Checks something (e.g., controller connected?)

// Global config table (0x38 bytes per entry, up to 0x1000 entries)
extern ControllerConfigEntry* DAT_011a0f28;

void __thiscall ControllerManager::applyControllerConfig(uint slotIndex)
{
    uint adjustedSlot;
    ControllerConfigEntry* configEntry;
    int slotOffset;

    // Clamp slot index: if > 15, add 0xF1 (maybe for extended slots?)
    adjustedSlot = slotIndex;
    if (slotIndex > 15) {
        adjustedSlot = slotIndex + 0xF1;
    }

    // If 'this' is null, skip to final call with 0
    if (this == nullptr) {
        goto final_call;
    }

    // Get config index from this object (offset +0x1c)
    uint configIdx = *(uint*)((uint8_t*)this + 0x1c);
    if (configIdx != 0) {
        // If config index is valid (<= 0xFFF), point to the entry in the global table
        if (configIdx <= 0xFFF) {
            configEntry = &DAT_011a0f28[configIdx]; // Each entry is 0x38 bytes
        } else {
            goto final_call; // Invalid index, skip
        }
    } else {
        configEntry = nullptr;
    }

    if (configEntry != nullptr) {
        // Check if we should skip vibration updates (FUN_00618c40 returns true?)
        if (!FUN_00618c40()) {
            // Update left motor (offset +0x20)
            slotOffset = slotIndex * 0xC;
            if (DAT_011f7450[slotOffset] != configEntry->leftMotor) {
                // Call vtable function at offset 0x114 on DAT_01205750 with (adjustedSlot, 7, leftMotor)
                (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                    (DAT_01205750, adjustedSlot, 7, configEntry->leftMotor);
                DAT_011f7450[slotOffset] = configEntry->leftMotor;
            }
            // Update right motor (offset +0x21)
            if (DAT_011f7451[slotOffset] != configEntry->rightMotor) {
                (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                    (DAT_01205750, adjustedSlot, 6, configEntry->rightMotor);
                DAT_011f7451[slotOffset] = configEntry->rightMotor;
            }
            // Update trigger motor (offset +0x22)
            if (DAT_011f7452[slotOffset] != configEntry->triggerMotor) {
                (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                    (DAT_01205750, adjustedSlot, 5, configEntry->triggerMotor);
                DAT_011f7452[slotOffset] = configEntry->triggerMotor;
            }
        }

        // Always update unknown motor1 (offset +0x23)
        slotOffset = slotIndex * 0xC;
        if (DAT_011f7453[slotOffset] != configEntry->unknownMotor1) {
            (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                (DAT_01205750, adjustedSlot, 10, configEntry->unknownMotor1);
            DAT_011f7453[slotOffset] = configEntry->unknownMotor1;
        }
        // Update unknown motor2 (offset +0x24) – set three times with same value (maybe left/right/trigger?)
        if (DAT_011f7454[slotOffset] != configEntry->unknownMotor2) {
            (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                (DAT_01205750, adjustedSlot, 1, configEntry->unknownMotor2);
            (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                (DAT_01205750, adjustedSlot, 2, configEntry->unknownMotor2);
            (*(void(__thiscall**)(void*, uint, int, uint8_t))(*(uint32_t*)DAT_01205750 + 0x114))
                (DAT_01205750, adjustedSlot, 3, configEntry->unknownMotor2);
            DAT_011f7454[slotOffset] = configEntry->unknownMotor2;
        }
        // Update int value (offset +0x28)
        if (*(int32_t*)((uint8_t*)&DAT_011f7458 + slotOffset) != configEntry->someIntValue) {
            (*(void(__thiscall**)(void*, uint, int, int32_t))(*(uint32_t*)DAT_01205750 + 0x114))
                (DAT_01205750, adjustedSlot, 4, configEntry->someIntValue);
            *(int32_t*)((uint8_t*)&DAT_011f7458 + slotOffset) = configEntry->someIntValue;
        }
    }

final_call:
    // Final call to set device type (or apply configuration) via DAT_0120595c vtable+0x104
    int32_t deviceType = (configEntry != nullptr) ? configEntry->deviceType : 0;
    (*(void(__thiscall**)(void*, uint, int32_t))(*(uint32_t*)DAT_0120595c + 0x104))
        (DAT_0120595c, adjustedSlot, deviceType);
}