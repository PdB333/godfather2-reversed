// FUNC_NAME: findEntry
// Function at 0x005e9d90: Generic key-value lookup in a container with two output values.
// Container structure (offsets relative to 'this'):
//   +0x04: uint* m_values          // Array of primary values (4 bytes each)
//   +0x08: int*  m_keys            // Array of keys (4 bytes each)
//   +0x0C: uint  m_count           // Number of entries
//   +0x14: UnknownStruct* m_extras // Array of 12-byte structures; offset 4 is secondary value

struct UnknownStruct {
    // unknown field at +0x00 (likely 4 bytes)
    uint secondaryValue; // at +0x04
    // unknown field at +0x08 (likely 4 bytes)
};

uint findEntry(int key, uint* outSecondary)
{
    uint thisReg; // 'this' pointer (in EDI)
    // Note: thisReg is actually the implicit 'this' from the calling convention.
    // In the real binary, it arrives in EDI for __thiscall.

    // Initialise return value to 0 (not found)
    uint result = 0;

    // Check if container is non-empty
    uint count = *(uint*)(thisReg + 0x0C);
    if (count != 0)
    {
        int* keys = *(int**)(thisReg + 0x08);
        uint index = 0;
        // Linear search for the key
        while (*keys != key)
        {
            ++index;
            ++keys;
            if (index >= count)
            {
                // Not found, return 0 without writing to outSecondary
                return result;
            }
        }

        // Found: retrieve primary value from m_values array
        uint* values = *(uint**)(thisReg + 0x04);
        result = values[index];

        // Retrieve secondary value from m_extras array (at offset 4 within each 12-byte struct)
        UnknownStruct* extras = *(UnknownStruct**)(thisReg + 0x14);
        *outSecondary = extras[index].secondaryValue;
    }

    return result;
}