// FUNC_NAME: SimObjectManager::createObject

// Function at 0x005e4f90: creates a new game object (allocates, constructs, registers, returns ID)
// Part of the EARS engine object factory pattern.

int SimObjectManager::createObject(int param2, int param3)
{
    int result = 0;
    // Check validity of 'this' pointer, param2, and compute internal data pointer
    if (this != 0 && param2 != 0)
    {
        int internalPtr = *(int *)(this + 0x10) + this;  // +0x10: offset to internal data structure
        if (internalPtr != 0 && this != (SimObjectManager *)-0x18)  // -0x18 sentinel check (likely artifact)
        {
            param2 = 0;
            int local8 = 0;
            // Retrieve creation parameters (e.g., resource handle, flags)
            bool success = getCreationParams(&param2, &local8);  // FUN_005e5d90
            if (success)
            {
                int objectId = generateObjectId();  // FUN_005e5e00: returns a new ID
                void *allocated = allocateMemory(0x20);  // FUN_009c8e50: allocate 32 bytes
                if (allocated != 0)
                {
                    int constructed = constructObject(param2);  // FUN_005e4220: initializer
                    if (constructed != 0)
                    {
                        param2 = constructed;  // track for finalisation
                        // Call virtual function via global vtable (DAT_01223510 + 0x10)
                        // This function presumably registers the object with the simulation
                        bool success2 = ((int (*)(int, int, int, int, int, int))(*DAT_01223510 + 0x10))
                                            (internalPtr, *(int *)(this + 0xc), *(int *)(this + 0x14),
                                             local8, constructed, param3);
                        if (success2)
                        {
                            finalizeCreation(&param2);  // FUN_005e6ce0: final registration/cleanup
                            return objectId;
                        }
                        freeMemory(constructed);  // FUN_009c8eb0: cleanup on failure
                    }
                    freeMemory(allocated);
                }
            }
        }
    }
    return result;
}