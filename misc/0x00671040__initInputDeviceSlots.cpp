// FUNC_NAME: initInputDeviceSlots
void __fastcall initInputDeviceSlots(uint32_t baseSlot)
{
    // Allocate and assign slot handles
    gSlotHandles[0] = baseSlot;                          // +0x00: base slot handle
    gSlotHandles[1] = allocateSlotHandle();              // +0x04: second slot handle
    gSlotHandles[2] = allocateSlotHandle();              // +0x08: third slot handle
    gSlotHandles[3] = allocateSlotHandle();              // +0x0C: fourth slot handle

    // Clear slot usage flags
    gSlotFlags[0] = 0;                                   // +0x00: flag byte for slot 0
    gSlotFlags[1] = 0;                                   // +0x01: flag byte for slot 1 (DAT_012066ac)
    gSlotFlags[2] = 0;                                   // +0x02: flag byte for slot 2 (DAT_012066ad)
}