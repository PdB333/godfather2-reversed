// FUNC_NAME: SlotAllocator::allocateSlot
// Address: 0x005e7370
// Role: Allocates a slot from a fixed-size byte-flag array, returns a token.
// Structure offsets: +0x18 = slotFlags[], +0x1c = maxSlots (byte), +0x1d = usedSlots (byte)
// Calling convention: ECX = this (param_1), EAX = baseID, ESI = outToken (written on success)

uint __fastcall SlotAllocator::allocateSlot(SlotAllocator* thisPtr, uint baseID, uint* outToken) {
    // Clear output token initially (prevent accidental uninitialized use)
    *outToken = 0;

    // Mask base ID to higher 24 bits (preserve high part, zero low byte)
    uint token = baseID & 0xFFFFFF00;

    // Check if there are free slots (used < cap)
    uint8 used = *(uint8*)((uint8*)thisPtr + 0x1d);
    uint8 cap  = *(uint8*)((uint8*)thisPtr + 0x1c);
    if (used < cap) {
        // Search for an empty slot (byte == 0) starting at offset +0x18
        uint8* slotArray = (uint8*)thisPtr + 0x18;
        for (uint i = 0; i < cap; ++i) {
            if (slotArray[i] == 0) {
                // Slot found, compute token: low byte as XOR with magic constant, rest from baseID mask
                if (i < 4) {
                    token = (i & 0xFF) ^ 0xAD103100;  // XOR low byte, high bits from constant
                    *outToken = token;                 // store in output pointer
                }
                // Mark slot as used
                slotArray[i] = 1;
                // Increment usage count
                *(uint8*)((uint8*)thisPtr + 0x1d) = used + 1;
                // Return token with low byte = 1 (indicates success)
                return (token & 0xFFFFFF00) | 1;
            }
        }
    }
    // No free slot, return original masked BaseID (higher bits unchanged)
    return baseID & 0xFFFFFF00;
}