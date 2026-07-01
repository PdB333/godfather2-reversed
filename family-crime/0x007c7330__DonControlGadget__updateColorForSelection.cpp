// FUNC_NAME: DonControlGadget::updateColorForSelection
void __thiscall DonControlGadget::updateColorForSelection(int* thisPtr)
{
    int playerObj = FUN_007ab1e0(); // likely returns current player object (Sentient or Player)
    if (playerObj != 0) {
        uint colorValue;
        // Check if player type byte at +0x1aa equals 2 (e.g., Don)
        if (*(char*)(playerObj + 0x1aa) == 2) {
            // Player is Don: compute color based on gadget selection state (offset 0x46)
            uint selectionState = thisPtr[0x46]; // +0x118
            colorValue = (selectionState != 2) ? 
                (0x3fa9044f + 0xc430dda0) :  // mask + const => final color
                0xc430dda0;                  // const alone
        } else {
            // Not Don: different color calculation
            uint selectionState = thisPtr[0x46];
            colorValue = (selectionState != 2) ? 
                (0xe52bf79d + 0xf643181f) : 
                0xf643181f;
        }
        // Call virtual function at vtable+0x2c (index 11) which sets color (RGBA 1,1,1,1)
        (*(void (__thiscall**)(int*, uint, float, float, float, float))(*thisPtr + 0x2c))
            (thisPtr, colorValue, 1.0f, 1.0f, 1.0f, 1.0f);
        // Play a sound or event with ID 0x1c
        FUN_007f6420(0x1c);
        return;
    }
    // No player object exists: set default state
    FUN_007c7130(1); // likely a fallback or reset
}