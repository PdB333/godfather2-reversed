// FUNC_004109f0: InputManager::updateControllerSlots
// Processes raw input data (in EAX) and updates controller slot states
// Slot structure at +0x2c, each 0x44 bytes, 16 slots
// Fields:
//   +0x10: ushort buttonFlags (bitmask: pressed/released)
//   +0x16: byte  buttonCurrent[16] (current analog value per button)
//   +0x26: byte  buttonHold[16] (hold counter / minimum value tracking)
//   +0x3e: byte  isActive (slot active flag)
// Manager fields:
//   +0x14: int   threshold (minimum value to consider button 'on')
//   +0x18: short activeButtonsMask (bitmask of buttons to process)
//   +0x1a: byte  buttonMargin[16] (hysteresis margin per button)

void InputManager::updateControllerSlots(void* rawInputData)
{
    byte* inputData = (byte*)rawInputData;  // from EAX, points to raw input buffer (16-byte rows per slot)

    if (*(short*)(this + 0x18) == 0)
        return;

    ControllerSlot* slots = (ControllerSlot*)(this + 0x2c);
    byte* margin = (byte*)(this + 0x1a);            // per-button margin array
    int threshold = *(int*)(this + 0x14);           // activation threshold

    for (int slotIdx = 0; slotIdx < 16; slotIdx++)
    {
        ControllerSlot* slot = &slots[slotIdx];     // each 0x44 bytes
        if (slot->isActive == 0)                   // +0x3e
            continue;

        for (int btn = 0; btn < 16; btn++)
        {
            uint btnMask = 1 << btn;
            if ((btnMask & *(ushort*)(this + 0x18)) == 0)   // skip if button not in active mask
                continue;

            byte newValue = inputData[btn];                  // raw input for this button
            byte curValue = slot->buttonCurrent[btn];        // +0x16
            byte* hold = &slot->buttonHold[btn];             // +0x26

            // Update hold to minimum observed value (debounce tracking)
            if ((uint)curValue < (uint)*hold)
                *hold = curValue;

            if ((uint)curValue >= (uint)threshold)
            {
                byte btnMargin = margin[btn];
                uint uVar6 = (uint)*hold;
                uint uVar7 = (uint)btnMargin;

                if ((int)curValue < (int)(newValue - btnMargin))
                {
                    // Button release detected (value drops too low)
                    slot->buttonFlags &= ~btnMask;           // +0x10 clear pressed bit
                    *hold = curValue;
                }
                else if (uVar6 != 0)
                {
                    if (uVar7 + uVar6 < (uint)curValue)
                    {
                        // Button press confirmed after hold period
                        slot->buttonFlags |= btnMask;        // +0x10 set pressed bit
                        *hold = 0;
                    }
                    else
                    {
                        // Not yet enough movement, clear pressed flag
                        slot->buttonFlags &= ~btnMask;
                    }
                }
            }
        }
        inputData += 0x10;   // next slot's raw data (16 bytes per slot)
    }
}