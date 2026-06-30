// FUNC_NAME: SomeManager::releaseAndCleanup (or destructor)

void __thiscall SomeManager::releaseAndCleanup(int thisPtr)
{
    // Release something at offset +0x40 (likely a pointer to a resource, e.g., audio stream)
    FUN_008c74d0(*(int *)(thisPtr + 0x40));

    // Check state at +0xc4: 0 = normal cleanup, 1 = special cleanup
    if (*(int *)(thisPtr + 0xc4) != 0)
    {
        if (*(int *)(thisPtr + 0xc4) != 1)
        {
            // Unknown state, just do base cleanup and return
            goto cleanup;
        }

        // State == 1: perform additional checks
        int unknownID = FUN_0084a410(); // Get some active/current ID
        if (unknownID != 0)
        {
            int localID = FUN_0084a410(); // Get local ID again?
            if (localID != *(int *)(thisPtr + 0x40))
            {
                return; // IDs don't match, skip cleanup
            }

            // Dereference pointer at +0xc0 (likely another object)
            int *objectPtrPtr = *(int **)(thisPtr + 0xc0);
            int object = *objectPtrPtr;

            int something = FUN_0084a640(); // Get another ID or count?
            // If difference is exactly 1, delete the object
            if (*(int *)(object + 4) - something == 1)
            {
                FUN_008c3240(objectPtrPtr); // Delete / remove object
            }
        }
    }

cleanup:
    // Base cleanup for this manager
    FUN_008c3e00(thisPtr);
    return;
}