// Xbox PDB: TNL::NetConnection::readConnectRequest
// FUNC_NAME: Character::isValid
// Address: 0x00654230
// This function validates that this Character instance is registered in the global character table.
// It compares the object's index (from virtual function at vtable+0x50) against the stored pointer.
// If mismatch, sets output string to "CHR_INVALID" and returns 0.

// External function used for debugging/validation (likely checks memory region or logs access)
extern void __cdecl debugValidateMemory(int size, void* ptr);

// Global table of character pointers (size unknown, stored at DAT_00f0cdb0)
extern Character** g_characterTable;

Character::isValid(Character* this, int characterId, char** outErrorMsg)
{
    int charIndex;
    Character* localThis;

    // Copy this pointer to a local for later comparison
    localThis = this;

    // Debug validation: treat the characterId and localThis as 32-byte regions
    debugValidateMemory(0x20, &characterId);
    debugValidateMemory(0x20, &localThis);

    // Get the character's index from the virtual function table
    charIndex = (*(int (__thiscall**)(Character*))(*(uint32_t*)this + 0x50))(this);

    if (characterId == charIndex)
    {
        charIndex = (*(int (__thiscall**)(Character*))(*(uint32_t*)this + 0x50))(this);
        // Check if the current object matches the registered pointer for this index
        if (localThis == g_characterTable[charIndex])
        {
            return 1; // Valid
        }
    }

    // Invalid: set error message
    *outErrorMsg = "CHR_INVALID";
    return 0;
}