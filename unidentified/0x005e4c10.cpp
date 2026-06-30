// FUN_NAME: EntityManager::validateHandleAndExecute
// Function address: 0x005e4c10
// This function looks up an entity handle and executes a callback if valid.
// It uses a handle format where lower 16 bits are an index into an array of 0x30-byte entries.
// The array starts at offset 0x10 from the base pointer stored in EDI (likely a member variable).
// ESI presumably points to the EntityManager instance (this).
// On success, calls FUN_00414aa0 with three values from this (fields at offsets 0, 4, 8).

bool __thiscall EntityManager::validateHandleAndExecute(uint32_t handle)
{
    uint16_t index = handle & 0xFFFF;
    if (index >= 0x200) // max 512 entries
    {
        return false;
    }

    // m_entryArray starts at offset 0x10 from the class base (passed in EDI)
    // Each entry is 0x30 bytes
    uint8_t* entryBase = reinterpret_cast<uint8_t*>(m_entryArrayBase); // unaff_EDI
    if (entryBase == nullptr)
    {
        return false;
    }
    uint8_t* entry = entryBase + 0x10 + index * 0x30; // offset to the entry
    if (entry == nullptr)
    {
        return false;
    }

    // Verify the handle stored at offset +0x2c matches
    uint32_t storedHandle = *reinterpret_cast<uint32_t*>(entry + 0x2C);
    if (storedHandle != handle)
    {
        return false;
    }

    // Execute the callback with three values stored in the manager (ESI fields)
    // These fields are at offsets 0, 4, 8 from this (unaff_ESI)
    FUN_00414aa0(m_field0, m_field1, m_field2); // unknown callback

    return true;
}