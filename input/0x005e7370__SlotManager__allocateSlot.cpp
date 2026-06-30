// FUNC_NAME: SlotManager::allocateSlot
uint __fastcall SlotManager::allocateSlot(SlotManager* this, uint inputFlags)
{
    // Offsets:
    // this+0x18: array of byte slots (pool)
    // this+0x1c: max slots count (byte)
    // this+0x1d: currently used slots count (byte)
    uint result;
    uint slotIndex;
    uint* outputID; // ESI points to a global or member where the allocated ID is stored

    outputID = 0; // *unaff_ESI = 0; but later reassigned; using 0 as placeholder -- actual pointer is a global
    *outputID = 0; // clear the output first

    result = inputFlags & 0xFFFFFF00; // preserve high 24 bits of input flags

    uint8 usedCount = *(uint8*)(this + 0x1d);
    uint8 maxSlots = *(uint8*)(this + 0x1c);

    if (usedCount < maxSlots && maxSlots != 0) {
        slotIndex = 0;
        // Scan pool for a free slot (byte == 0)
        while (*(char*)(this + 0x18 + slotIndex) != '\0') {
            slotIndex++;
            if (maxSlots <= (int)slotIndex) {
                return result; // no free slot found, return unchanged
            }
        }
        if ((byte)slotIndex < 4) {
            // only allocate from first 4 slots
            uint id = slotIndex & 0xFF;
            result = id ^ 0xAD103100; // compute a unique ID
            *outputID = result; // store it via global pointer
        }
        // Mark slot as used
        *(char*)(this + 0x1d) = usedCount + 1;
        *(char*)(this + 0x18 + slotIndex) = 1;
        // Construct final return value: high 24 bits = (result>>8), low 8 bits = 1
        result = (result >> 8) & 0xFFFFFF00 | 1;
    }
    return result;
}