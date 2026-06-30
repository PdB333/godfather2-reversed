// FUNC_NAME: GameObject::conditionalUpdate

void __thiscall GameObject::conditionalUpdate(int thisPtr) {
    // Check bit 6 of the flags at offset +0x8E0.
    // If the bit is clear, perform the associated update (FUN_00800880).
    uint flags = *(uint*)(thisPtr + 0x8E0);
    if ((flags & (1 << 6)) == 0) {
        FUN_00800880(); // Likely rebuilds or processes some cached data
    }
}