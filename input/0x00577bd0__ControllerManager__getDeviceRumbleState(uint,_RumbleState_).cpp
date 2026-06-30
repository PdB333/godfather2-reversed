// FUNC_NAME: ControllerManager::getDeviceRumbleState(uint, RumbleState*)
// Address: 0x00577bd0
// This function retrieves rumble state (likely motor speeds) for a controller device.
// It uses an internal mapping array at +0xB4 to translate a device index to a physical slot,
// then reads a 0x40-byte rumble state entry from an array at +0xB8.
// The rumble data is stored at offsets +0x30, +0x34, +0x38 within each entry.

bool __fastcall ControllerManager::getDeviceRumbleState(uint deviceIndex, RumbleState* outState)
{
    // +0xB4: Pointer to an array mapping logical device indices to physical controller slots
    // The mapping is byte-sized; 0xFF means unmapped.
    if (this->deviceMapping != NULL)
    {
        uint mappedSlot = this->deviceMapping[deviceIndex];
        if (mappedSlot != 0xFF)
        {
            // +0xB8: Pointer to an array of rumble state structs, each 0x40 bytes
            if (this->rumbleStateArray != NULL)
            {
                uint entryOffset = mappedSlot * 0x40;
                uint8_t* entryBase = this->rumbleStateArray + entryOffset;
                // Read three float/int rumble values at offsets +0x30, +0x34, +0x38
                outState->leftMotor  = *(float*)(entryBase + 0x30);
                outState->rightMotor = *(float*)(entryBase + 0x34);
                outState->trigger    = *(float*)(entryBase + 0x38);
                return true;
            }
        }
    }
    outState->leftMotor  = 0.0f;
    outState->rightMotor = 0.0f;
    outState->trigger    = 0.0f;
    return false;
}