// FUNC_NAME: InputDeviceManager::applyControllerState
// Address: 0x00566fb0
// This function applies a new controller state (XInput data for 16 slots, 0x44 bytes each = 0x440 total)
// by deep-copying the provided buffer into an internally allocated block.
// It then checks for an active input device and invokes a callback if registered.
// Finally, it updates internal flags to indicate new data is available.

void __thiscall InputDeviceManager::applyControllerState(uint8_t* controllerData)
{
    // Allocate and copy controller state buffer (16 slots × 0x44 bytes)
    if (controllerData != nullptr)
    {
        // Allocate 0x440 bytes for 16 controller slots (0x44 per slot)
        uint8_t* newBuffer = (uint8_t*)operator_new(0x440);  // FUN_009c8e50 (likely operator new)
        if (newBuffer != nullptr)
        {
            // Copy 0x440 bytes from input buffer (0x110 dwords)
            memcpy(newBuffer, controllerData, 0x440);
        }
        // Store the new buffer at offset +0x11C
        *(uint8_t**)(this + 0x11C) = newBuffer;
    }

    // Get current active input device (e.g., the controller that was last used)
    void* activeDevice = (void*)FUN_00ad8d40();  // getActiveInputDevice() or similar

    // If an active device exists and we have a callback registered, invoke it
    if (activeDevice != nullptr)
    {
        void (*deviceCallback)(void*) = *(void (__thiscall**)(void*))(this + 0x54);
        if (deviceCallback != nullptr)
        {
            deviceCallback(activeDevice);
        }
    }

    // Mark that new controller state was applied (bit 0x20 in flags at +0x2C)
    *(uint32_t*)(this + 0x2C) |= 0x20;

    // Set internal state to 8 (e.g., "controller state ready")
    *(int32_t*)(this + 0x10) = 8;

    return;
}