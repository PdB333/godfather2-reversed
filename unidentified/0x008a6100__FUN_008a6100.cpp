// FUNC_NAME: UnknownClass::countObjectsWithTypeAndFlag

short UnknownClass::countObjectsWithTypeAndFlag(uint someParam, int targetType)
{
    short count = 0;
    // Initialize iterator over internal list (likely a linked list or array)
    // FUN_004bab20 sets up the iterator state
    Iterator iter;
    FUN_004bab20(&iter, someParam, targetType);

    while (iter.current != 0 || iter.end != 0) // while loop as decompiled; iter.current and iter.end are local_c and local_8
    {
        // Get current object from iterator (call first function pointer)
        int objPtr = (*(code *)iter.getFunc)();

        // Check if object has bit 1 at offset 0x1c and type at offset 0x10 matches
        if ( (*(uint *)(objPtr + 0x1c) >> 1 & 1) != 0 && *(int *)(objPtr + 0x10) == targetType )
        {
            count++;
        }

        // Advance iterator (call third function pointer)
        (*(code *)iter.nextFunc)();
    }
    return count;
}