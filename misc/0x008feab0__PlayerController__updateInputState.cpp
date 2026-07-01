// FUNC_NAME: PlayerController::updateInputState
void __thiscall PlayerController::updateInputState(uint inputFlags)
{
    // Set three flags from bits of inputFlags
    // +0x7c: flagA (bit0)
    // +0x84: flagB (bit1)
    // +0x8c: flagC (bit2)
    *(byte *)(this + 0x7c) = (byte)inputFlags & 1;
    *(byte *)(this + 0x84) = (byte)(inputFlags >> 1) & 1;
    *(byte *)(this + 0x8c) = (byte)(inputFlags >> 2) & 1;

    // Check pointer at +0xC8 (200) – likely a handle or object pointer
    int* ptr = *(int**)(this + 0xC8);
    if (ptr != nullptr && ptr != (int*)0x48) {
        int base = (int)ptr - 0x48; // subtract offset to get base of some structure
        // Check bit 29 at offset +0x5c of that structure
        if ((*(uint*)(base + 0x5c) >> 0x1d & 1) != 0) {
            FUN_008ff3f0(this); // likely triggers some action
        }
    }

    // Compare current value from external function with stored value at +0xDC
    int newValue = FUN_008fe480(); // returns some state or time
    if (newValue != *(int*)(this + 0xDC)) {
        FUN_008fddc0(); // reset or update something
        FUN_008fe5e0(newValue); // apply new value
    }
}