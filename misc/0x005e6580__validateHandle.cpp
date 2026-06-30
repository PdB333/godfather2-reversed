// FUNC_NAME: validateHandle
// Address: 0x005e6580
// Validates a handle by checking its ID, index, and magic number, then acquires a reference.
// The handle format: lower 16 bits are index into a table, upper bits are magic/ID.
// Table has 512 entries (0x200), each 0x30 bytes.
// Global pointer to table base: DAT_012234bc (g_handleTableBase)

bool validateHandle(uint handleId)
{
    uint idx;
    int structPtr;
    bool result;

    result = false;
    // Check index range (lower 16 bits)
    idx = handleId & 0xFFFF;
    if (idx < 0x200)
    {
        // Compute pointer to structure: base + idx*0x30 + 0x10 (some offset)
        structPtr = (int)((idx * 0x30) + 0x10 + DAT_012234bc);
        if (structPtr != 0)
        {
            // Check that the stored handle at offset 0x2C matches our handle
            if (*(uint *)(structPtr + 0x2C) == handleId)
            {
                // Valid handle: acquire reference/lock
                FUN_00414aa0();  // likely reference count increment or lock
                result = true;
            }
        }
    }
    return result;
}