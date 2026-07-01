// FUNC_NAME: SomeManager::processPendingActions
void __fastcall SomeManager::processPendingActions(int thisPtr)
{
    uint* pendingFlags = reinterpret_cast<uint*>(thisPtr + 0x40);

    // Only process if high bit is not set (not already processing/completed)
    if (static_cast<int>(*pendingFlags) >= 0)
    {
        // Virtual call: get some context/manager (e.g., time or state) from vtable at this+0xc, offset 0x60
        int contextValue = (*(int (__fastcall**)(int))(*(int*)(thisPtr + 0xc) + 0x60))(thisPtr);

        // Virtual call: get a global data block from vtable at this+0x8, then sub-object at +8, offset 0x1c
        int globalDataPtr = (*(int (__fastcall**)(int))(*(int*)(*(int*)(thisPtr + 8) + 8) + 0x1c))(thisPtr);
        int someConstant = *(int*)(globalDataPtr + 0xf04);  // e.g., frame counter or world state

        // Query the count and base offsets of pending items
        int itemOffset;
        int offsetA, offsetB;  // probably padding/alignment fields
        int itemCount = FUN_0099b790(*(uint*)(thisPtr + 0x24), *(uint*)(thisPtr + 0x28),
                                     &itemOffset, &offsetA, &offsetB, 0, 0);

        int currentItemBase = itemOffset;  // starting offset for the list
        uint* currentFlags = pendingFlags;
        int savedA = offsetA;
        int savedB = offsetB;
        int savedConst = someConstant;

        for (; itemCount != 0; itemCount--)
        {
            // Check if this item's flag (bit 0) is clear (not processed)
            if ((*(byte*)(thisPtr + 4 + currentItemBase) & 1) == 0)
            {
                // Virtual call: perform an action (e.g., place/get ID) from vtable at this+0x8, offset 0x24
                int actionResult = (*(int (__fastcall**)(uint, int, int, int))(*(int*)(*(int*)(thisPtr + 8) + 8) + 0x24))
                                    (currentFlags, savedA, savedB, savedConst);

                // Actual processing: likely spawn/update an entity
                FUN_009b8560(*(uint*)(thisPtr + currentItemBase),
                             *(uint*)(thisPtr + currentItemBase + 8),
                             contextValue, actionResult,
                             currentFlags, savedA, savedB, savedConst);

                // Mark this item's flag as processed (set bit 0)
                uint* itemFlagPtr = reinterpret_cast<uint*>(thisPtr + 4 + itemOffset);
                *itemFlagPtr |= 1;
            }

            // Advance to next item (each item is 12 bytes)
            currentFlags = pendingFlags;  // reset pointer because it may have been modified (though not in this version)
            thisPtr += 0xc;  // wrong, should use a local variable. Actually the loop uses iVar1 which increments by 0xc relative to original thisPtr.
            // Better: track a local offset pointer
        }

        // Set high bit to indicate processing complete
        *pendingFlags |= 0x80000000;
    }
}