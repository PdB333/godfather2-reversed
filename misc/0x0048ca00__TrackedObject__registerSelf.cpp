// FUNC_NAME: TrackedObject::registerSelf

void __thiscall TrackedObject::registerSelf( int thisPtr, uint32_t *pRegistrySlot )
{
    // Check if not already registered (flag at +0x0C)
    if ( *(char *)(thisPtr + 0x0C) == '\0' )
    {
        // Retrieve the identifier/data stored at +0x04
        uint32_t data1 = *(uint32_t *)(thisPtr + 0x04);

        // Global manager structure: DAT_01206880 points to a manager object;
        // offset +0x14 is a write cursor into a dynamic array (linear allocator)
        int *pCursor = (int *)( g_globalManager + 0x14 );

        // Initialize the slot with a known vtable or type marker (PTR_LAB_01123d28)
        *(int **)( *pCursor ) = &PTR_LAB_01123d28;
        // Advance cursor
        *pCursor += 4;

        // Store the object's data into the next slot
        *(uint32_t *)( *pCursor ) = data1;
        // Advance cursor again
        *pCursor += 4;

        // Mark as registered
        *(char *)(thisPtr + 0x0C) = 1;
    }

    // Call final processing with: slot index (from pRegistrySlot), data1 (+0x04), data2 (+0x08)
    // pRegistrySlot is a pointer to a slot ID; dereferenced to get the actual index
    FUN_0048c930( *pRegistrySlot, *(uint32_t *)(thisPtr + 0x04), *(uint32_t *)(thisPtr + 0x08) );
}