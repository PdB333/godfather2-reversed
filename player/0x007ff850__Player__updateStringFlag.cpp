// FUNC_NAME: Player::updateStringFlag
void __thiscall Player::updateStringFlag(int thisPtr, char* stringParam)
{
    // +0x8dc: currentScreenId (int)
    // +0x4a4: flags (uint) - bit 0 is "stringFlag" or "needsUpdate"
    // DAT_00e2e37c: global constant screen ID (e.g., kMainMenuScreenId)

    int currentScreenId = *(int*)(thisPtr + 0x8dc);
    int mainMenuScreenId = DAT_00e2e37c; // global constant

    // If the current screen is not the main menu, or the string is empty,
    // then update the flag.
    if ((currentScreenId != mainMenuScreenId) || (*stringParam == '\0'))
    {
        if (*stringParam == '\0')
        {
            // Empty string: set the flag (bit 0)
            *(uint*)(thisPtr + 0x4a4) |= 1;
            return;
        }
        // Non-empty string: clear the flag (bit 0)
        *(uint*)(thisPtr + 0x4a4) &= 0xfffffffe;
    }
    // If current screen is main menu and string is non-empty, do nothing.
}