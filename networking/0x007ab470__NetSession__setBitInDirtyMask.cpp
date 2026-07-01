// FUNC_NAME: NetSession::setBitInDirtyMask
void __thiscall NetSession::setBitInDirtyMask(uint slotIndex) {
    // Get base pointer from this+0x58 (likely a large internal state struct)
    uint* basePtr = *(uint**)(this + 0x58);
    // Bitfield array starts at offset 0x249c from basePtr (dirty mask for 32-slot windows)
    uint* word = (uint*)((uint)basePtr + 0x249c) + (slotIndex >> 5);
    *word |= 1 << (slotIndex & 0x1f);
}