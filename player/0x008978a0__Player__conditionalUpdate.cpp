// FUNC_NAME: Player::conditionalUpdate

// Address: 0x008978a0
// Role: Conditionally triggers FUN_008977c0 based on flags in 'this' and the owner object

// This method checks several conditions before calling the target function:
// - Bit1 of flags at this+0x58 must be set
// - The owner pointer at this+0x00 must be non‑null
// - Byte at owner+0x894 must have bit0 cleared
// - Uint at owner+0x894 must have bit3 cleared

void __thiscall Player::conditionalUpdate(int* thisPtr) {
    int* ownerPtr;

    // Check bit1 of flags at offset +0x58 (thisPtr[0x16] * 4 = 0x58)
    if ((((uint)thisPtr[0x16] >> 1 & 1) != 0) &&
        // Dereference owner pointer at offset +0x00
        (ownerPtr = (int*)*thisPtr, ownerPtr != (int*)0) &&
        // Check bit0 of byte at owner+0x894
        ((*(byte*)((int)ownerPtr + 0x894) & 1) == 0) &&
        // Check bit3 of uint at owner+0x894
        ((*(uint*)((int)ownerPtr + 0x894) >> 3 & 1) == 0)) {
        // All conditions met – call the target function
        FUN_008977c0();
    }
}