// FUNC_NAME: EARSObject::destroy

void EARSObject::destroy(void)
{
    // Check if there's a resource handle at +0xA0 (pointer) and +0xA4 (some ID)
    if (*(int *)(this + 0xA0) != 0)
    {
        FUN_004f7bc0(*(undefined4 *)(this + 0xA0), *(undefined4 *)(this + 0xA4)); // freeResource
    }

    // State byte at +0x5B: if not 0, 3, or 5, remove from world
    char state = *(char *)(this + 0x5B);
    if ((state != '\0') && (state != '\x03') && (state != '\x05'))
    {
        FUN_005117c0(); // removeFromWorld
    }

    // Set destruction flag (bit 3) in flags at +0x2C
    *(uint *)(this + 0x2C) |= 8;

    // Number of children at +0x58 (short)
    int childCount = (int)*(short *)(this + 0x58);

    // If flag at +0x2C bit 9 (0x200) is set, decrement global count and skip children
    if ((*(uint *)(this + 0x2C) & 0x200) != 0)
    {
        _DAT_01194a98 -= childCount; // Global child count
        return;
    }

    // Iterate over children array at +0xB0 (pairs of ints)
    if (childCount > 0)
    {
        int *childArray = (int *)(this + 0xB0);
        for (int i = 0; i < childCount; i++)
        {
            int childPtr = childArray[i * 2];
            int childParam = childArray[i * 2 + 1];
            if ((childPtr != 0) && (DAT_0112509c != 0)) // Global flag for cleanup
            {
                FUN_00513d50(childPtr, childParam); // cleanupChild
            }
        }
    }
}