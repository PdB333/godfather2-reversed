// FUNC_NAME: InputManager::checkControllerStickStatus
uint __fastcall InputManager::checkControllerStickStatus(InputManager* this, uint eaxValue)
{
    // Offsets:
    // +0x000: ControllerSlot mSlots[16] (size 0x44 each)
    //    +0x034: leftStickRaw (uint, interpreted as float after mask)
    //    +0x038: rightStickRaw (uint, interpreted as float after mask)
    // +0x52d: byte mSlotFlags[16] (non-zero = slot active)
    // +0x564: byte mCurrentSlotIndex

    const uint AXIS_DEADZONE_MASK = DAT_00e44680;   // e.g., clears sign bits
    const float AXIS_DEADZONE_THRESHOLD = DAT_00e44598; // e.g., 0.2f

    uint result = eaxValue & 0xFFFFFF00;  // Preserve high 24 bits from previous state

    byte slotIndex = this->mCurrentSlotIndex;   // +0x564
    if (slotIndex < 16 && this->mSlotFlags[slotIndex] != 0)   // +0x52d[slotIndex]
    {
        ControllerSlot* slot = &this->mSlots[slotIndex];   // base + slotIndex * 0x44

        // Read masked axis values as floats
        float leftAxis  = (float)(slot->leftStickRaw  & AXIS_DEADZONE_MASK);   // +0x34
        float rightAxis = (float)(slot->rightStickRaw & AXIS_DEADZONE_MASK);   // +0x38

        // Derive slot ID from pointer (low 24 bits of (pointer >> 8))
        uint slotId = ((uint)(slot) >> 8) & 0xFFFFFF;

        if (leftAxis <= AXIS_DEADZONE_THRESHOLD && rightAxis <= AXIS_DEADZONE_THRESHOLD)
        {
            // Both sticks within dead zone → return slotId in high 24 bits, low byte = 0
            result = slotId << 8;
        }
        else
        {
            // At least one stick outside dead zone → set low byte to 1
            result = (slotId << 8) | 1;
        }
    }

    return result;
}