// FUNC_NAME: InputDeviceManager::updateDeviceSlot
// Address: 0x0052e710
// Updates state for a specific device slot (0-31) and triggers a refresh.
// Uses global arrays: deviceInfoArray (0x01219390, 0x18 bytes per entry),
// deviceActiveFlags (0x01219808), deviceValues (0x01219788).

struct DeviceInfo {
    /* +0x00 */ uint8_t unknown[4];
    /* +0x04 */ uint32_t flags;
    /* +0x08 */ uint8_t unknown2[4];
    /* +0x0C */ int32_t value;
};

// Global arrays (likely members of InputDeviceManager singleton)
extern DeviceInfo deviceInfoArray[32];  // 0x01219390
extern bool deviceActiveFlags[32];      // 0x01219808
extern int32_t deviceValues[32];        // 0x01219788

// Forward declaration of internal refresh function
void InputDeviceManager::refreshDevices();

void __fastcall InputDeviceManager::updateDeviceSlot(void* this, uint32_t slotIndex) {
    // Validate slot index (max 32 slots, e.g., 16 XInput controllers + keyboard/mouse)
    if (slotIndex >= 0x20) {   // 32
        goto callRefresh;
    }

    // Check bit 24 of the device's flags (e.g., connected/active flag)
    if ((deviceInfoArray[slotIndex].flags & 0x1000000) != 0) {
        deviceActiveFlags[slotIndex] = true;
        deviceValues[slotIndex] = deviceInfoArray[slotIndex].value;
    } else {
        deviceActiveFlags[slotIndex] = false;
        deviceValues[slotIndex] = 0;
    }

callRefresh:
    // Update overall device state (e.g., propagate changes to input system)
    InputDeviceManager::refreshDevices();
}