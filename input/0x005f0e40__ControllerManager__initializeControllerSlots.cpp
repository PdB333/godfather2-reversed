// FUNC_NAME: ControllerManager::initializeControllerSlots
// Address: 0x005f0e40
// Role: Initializes an array of controller slots (two slots, each with 12-byte header + 0x80-byte buffer).
// Likely part of Input/Controller system (16 slots of 0x44 bytes elsewhere, but this is a specialized init).
// Constants: 0x80 = buffer size, 0x44 = unknown (may be slot count or another size).

struct ControllerSlot {
    uint32_t field_0;    // +0x00: cleared to 0
    uint32_t field_4;    // +0x04: cleared to 0
    uint16_t type;       // +0x08: set to 0x80
    uint16_t flags;      // +0x0A: set to 0
    uint8_t  buffer[0x80]; // +0x0C: actual data buffer (cleared by FUN_005dbc10)
};

// Size: 0x80 + 12 = 0x8C? Actually buffer starts at offset 12, but buffer size is 0x80, so slot size = 0x8C.
// But the loop step is 12 bytes, not 0x8C. Inconsistency suggests the header is only the first 12 bytes,
// and the buffer is attached separately or the loop actually increments by sizeof(ControllerSlot) = 0x8C / 4 = 0x23? Not 3.
// Decompiler may have misrepresented step due to type confusion. We keep the code as decompiled.

void __fastcall ControllerManager::initializeControllerSlots(ControllerSlot* slotArray)
{
    // Allocate or register slot array: FUN_005f5830(0x80, 0x44, &someHandler)
    // This may be a pool or callback registration.
    // Inline replace: someInitFunction(0x80, 0x44, &handlerAt005f0e20);
    // FUN_005f5830 internal purpose unknown, but likely initializes a factory or memory pool.

    ControllerSlot* endSlot = slotArray + 6;  // 6 * sizeof(ControllerSlot*) = 24 bytes? Actually +6 on pointer increments by 24 bytes if step=4? No: +6 on pointer adds 6*sizeof(*slotArray)=6*4=24 bytes. So loop runs over two slots spaced 12 bytes (3*4) apart. This matches array of two 12-byte headers, not full slot.

    for (ControllerSlot* slot = slotArray; slot < endSlot; slot = slot + 3) // step 3 means 12-byte increments
    {
        if (slot != NULL)
        {
            slot->field_0 = 0;
            slot->field_4 = 0;
            slot->type   = 0x80;
            slot->flags  = 0;

            // Clear the following 0x80 bytes in the buffer region.
            // FUN_005dbc10 likely is memset or buffer initializer.
            FUN_005dbc10(slot, 0x80);  // Second argument is size to clear.
        }
    }
}