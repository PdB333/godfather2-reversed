// FUNC_NAME: FamilyManager::initializeFamilyCategoryHashes
// Address: 0x008c7130
// Initializes the family category hash array (4 families) by concatenating "FamilyCategory_" with the family name and storing the hash.
// The family names are retrieved via getFamilyCategoryName() based on index (0-3).
// Uses EA string concatenation and hashing functions.

void __thiscall FamilyManager::initializeFamilyCategoryHashes(FamilyManager* this)
{
    // Array at offset +0x14 holds 4 uint32 family category hashes
    uint32* hashArray = (uint32*)((uint8*)this + 0x14);

    for (int i = 0; i < 4; ++i)
    {
        // Get the family name string for this index (e.g., "Corleone")
        const char* familyName = getFamilyCategoryName(i);

        // Concatenate "FamilyCategory_" with the family name
        // FUN_00401d30 likely returns a pointer to a temporary concatenated string
        char* concatenated = concatStrings("FamilyCategory_", familyName);

        // Use default string if concatenation failed
        const char* hashInput = (concatenated != nullptr) ? concatenated : &FALLBACK_STRING; // e.g., "FamilyCategory_Unknown"

        // Compute hash of the concatenated string (probably CRC32 or similar)
        uint32 hash = computeStringHash(hashInput);

        // Store the hash
        hashArray[i] = hash;

        // Free the concatenated string if it was dynamically allocated
        if (concatenated != nullptr)
        {
            // Deallocation function, likely free or string destructor
            deallocateString(concatenated);
        }
    }
}