// FUNC_NAME: AnimController::updateAnimDataPointer
void __thiscall AnimController::updateAnimDataPointer(void)
{
    // Global state checks: game mode must be 9 and a flag must be 0
    if (g_gameMode == 9 && g_someFlag == 0)
    {
        // Calculate offset into an array of objects (size 0xD4) using 'this' as index
        int objectBase = *reinterpret_cast<int*>(this) * 0xD4 + 4 + g_objectArrayBase;

        // Read field at offset 0xB4 (likely animation state index)
        int animState = *reinterpret_cast<int*>(objectBase + 0xB4);

        // If state is not 9, update the global animation data pointer
        if (animState != 9)
        {
            // Read field at offset 0xB8 (likely animation type index)
            int animType = *reinterpret_cast<int*>(objectBase + 0xB8);

            // Compute pointer into a 2D array of 16-byte entries: [animType][animState]
            g_currentAnimData = reinterpret_cast<uint8_t*>(
                &g_animDataArray + (animType * 0x11 + animState) * 0x10
            );
        }
    }
}