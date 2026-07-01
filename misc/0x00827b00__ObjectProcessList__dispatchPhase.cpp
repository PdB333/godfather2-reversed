// FUNC_NAME: ObjectProcessList::dispatchPhase
// Function address: 0x00827b00
// This function manages a dynamic list of handler objects (processors) that
// are called for each phase. It supports creating new handlers from a global
// factory table keyed by an identifier, and dispatching virtual calls to
// handlers according to the phase (0=process, 1/2=return if handled).
// The object also stores a 4-int GUID used to match with the incoming guid pointer.

char __thiscall ObjectProcessList::dispatchPhase(int* thisPtr, int handlerId, int* pGuid, undefined4 arg4, int arg5, int phase)
{
    int guidCompare[4]; // stack local for temp? Not used as array but as individual.
    int* pNewHandler; // pointer to newly allocated handler
    int oldNext; // linked list next pointer save
    uint i;
    char result;
    char retByte;
    int* pSlot;

    if (phase == 0)
    {
        // Phase 0: iterate over existing handlers, call virtual function at offset 0x14 for each.
        // If that returns non-zero, then call offset 0x18 with the full parameter set and return its result.
        i = 0;
        if (thisPtr[2] != 0) // count
        {
            do
            {
                // Get handler pointer from slot array (each slot is 8 bytes: pointer to handler, then next link)
                int* handler = *(int**)(thisPtr[1] + i * 8);
                // Call virtual function at offset 0x14 (likely a test/query function)
                result = (*(char (__thiscall**)(void*))(*(int*)handler + 0x14))();
                if (result != 0)
                {
                    // If test passes, call the actual process function at offset 0x18
                    retByte = (*(char (__thiscall**)(int, int*, undefined4, int))(*(int*)handler + 0x18))(handlerId, pGuid, arg4, arg5);
                    return retByte;
                }
                i++;
            } while (i < (uint)thisPtr[2]);
        }

        // Not found in existing handlers: try to create a new one from the global factory table.
        // The global table g_pHandlerFactoryTable stores 8-byte entries: [0]=factory function pointer, [4]=handlerId for which it's registered.
        i = 0;
        if (g_handlerFactoryCount != 0)
        {
            do
            {
                if (*(int*)(g_pHandlerFactoryTable + 4 + i * 8) == handlerId && *(int*)(g_pHandlerFactoryTable + i * 8) != 0)
                {
                    // Call the factory function to create a new handler object
                    pNewHandler = (int*)(**(code**)(g_pHandlerFactoryTable + i * 8))();
                    // Insert the new handler into the local list (intrusive linked list)
                    oldNext = pNewHandler[1]; // save original next pointer
                    pNewHandler[1] = (int)&pNewHandler; // redirect next to stack? Actually this is a dummy sentinel setup.

                    // Set the container pointer in the new handler
                    pNewHandler[2] = (int)thisPtr;

                    // Check if array needs to grow
                    int capacity = thisPtr[3];
                    if (thisPtr[2] == capacity)
                    {
                        int newCapacity;
                        if (capacity == 0)
                            newCapacity = 1;
                        else
                            newCapacity = capacity * 2;
                        // Call growth routine (FUN_00827340)
                        FUN_00827340();
                    }

                    // Get pointer to the slot that will hold the new handler
                    pSlot = (undefined4*)(thisPtr[1] + thisPtr[2] * 8);
                    // Increment count
                    thisPtr[2] = thisPtr[2] + 1;
                    if (pSlot != (undefined4*)0x0)
                    {
                        // Write the handler pointer into the slot
                        *pSlot = pNewHandler;
                        // Write the next pointer (the old saved next) into the slot's second field
                        pSlot[1] = 0; // initially set to 0? Actually the next field seems to be saved from the handler's old next
                        if (pNewHandler != (int*)0x0)
                        {
                            pSlot[1] = pNewHandler[1]; // put old next into slot's second field
                            // Now update the handler's next to point back to the slot
                            pNewHandler[1] = (int)pSlot;
                        }
                    }

                    // After insertion, call the handler's process function at offset 0x18
                    retByte = (*(char (__thiscall**)(int, int*, undefined4, int))(*(int*)pNewHandler + 0x18))(handlerId, pGuid, arg4, arg5);
                    return retByte;
                }
                i++;
            } while (i < g_handlerFactoryCount);
        }
    }
    else if ((phase == 1 || phase == 2) && thisPtr[2] != 0)
    {
        // Phase 1 or 2: iterate over existing handlers and call offset 0x18, return 1 if any returns 1.
        i = 0;
        do
        {
            int* handler = *(int**)(thisPtr[1] + i * 8);
            result = (*(char (__thiscall**)(int, int*, undefined4, int))(*(int*)handler + 0x18))(handlerId, pGuid, arg4, arg5);
            if (result == 1)
                return 1;
            i++;
        } while (i < (uint)thisPtr[2]);
    }

    // If no handler processed the request, check if the incoming GUID matches this object's stored GUID.
    // Stored GUID is at offsets thisPtr[9..12] (0x24,0x28,0x2c,0x30)
    if (pGuid[0] == thisPtr[9] && pGuid[1] == thisPtr[10] && pGuid[2] == thisPtr[11] && pGuid[3] == thisPtr[12])
    {
        // If match, call virtual function at offset 0x4 (likely self-processing)
        (*(void (__thiscall**)(int*))(*(int*)thisPtr + 4))(thisPtr);
        return 1;
    }
    return 0;
}