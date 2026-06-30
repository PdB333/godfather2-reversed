// FUNC_NAME: ObjectContainer::clearAndDestroyAll

void __fastcall ObjectContainer::clearAndDestroyAll(void *thisPtr)
{
    uint32_t objectCount = *(uint32_t *)((int)thisPtr + 0x29c);    // number of objects
    int **objectArray = *(int ***)((int)thisPtr + 0x298);         // array of object pointers
    uint32_t i;

    // First pass: set deactivation flags on each object
    if (objectCount != 0)
    {
        for (i = 0; i < objectCount; i++)
        {
            int *object = objectArray[i];
            if (object != 0)
            {
                // Check if bit 0x20000 (deactivated? pending destroy?) is not set
                if ((*(uint32_t *)(object + 0x3) & 0x20000) == 0)   // +0x0c: flags
                {
                    // Set bit 0x20000
                    *(uint32_t *)(object + 0x3) |= 0x20000;
                    FUN_0051b120();  // Notify object being deactivated
                }
                // Clear bit 0x40000 (active flag?)
                *(uint32_t *)(object + 0x3) &= 0xFFFBFFFF;
            }
        }
    }

    // Second pass: clear array entries and zero out object's +0x08 field
    int remaining = *(int *)((int)thisPtr + 0x29c);
    while (remaining > 0)
    {
        remaining--;
        int **entry = objectArray + remaining;
        int *object = *entry;
        if (object != 0)
        {
            *(int *)(object + 0x2) = 0;   // +0x08: some pointer/reference
            *entry = 0;
        }
    }

    // Reset count, free array memory, clear related fields
    *(int *)((int)thisPtr + 0x29c) = 0;           // count = 0
    FUN_009c8f10(*(int *)((int)thisPtr + 0x298)); // free the object array
    *(int *)((int)thisPtr + 0x298) = 0;           // array pointer = 0
    *(int *)((int)thisPtr + 0x2a0) = 0;           // some other counter/pointer

    // Clear bit 8 (0x100) in flags at +0x184
    *(uint32_t *)((int)thisPtr + 0x184) &= 0xFFFFFEFF;
}