// FUNC_NAME: CharacterManager::validateCharacter

// Address: 0x00654230
// Validates that the given character identifier (hash) matches the current character object.
// Returns 1 on success, 0 on failure with error string output.

int __thiscall CharacterManager::validateCharacter(int *characterId, const char **outError)
{
    int savedThis = this;                     // Preserve this pointer for transformation
    int localHash;                            // Hash after transformation

    // Transform the input character ID (possibly 32-byte buffer or hash seed)
    FUN_0064b9e0(0x20, characterId);          // 0x20 = 32 bytes, could be CRC32 or decryption

    // Transform the saved this pointer (likely the same algorithm)
    FUN_0064b9e0(0x20, &savedThis);           // Treat savedThis as a 32-byte structure?

    // Call virtual function at vtable offset 0x50 (index 20) – returns a character ID hash
    int currentId = (**(code **)(*this + 0x50))();

    if (*characterId == currentId)
    {
        // Re-fetch the ID (might be a static hash or status)
        currentId = (**(code **)(*this + 0x50))();

        // Global character lookup table indexed by character ID
        if (savedThis == g_characterTable[currentId])
        {
            return 1; // Valid character
        }
    }

    *outError = "CHR_INVALID";
    return 0;
}