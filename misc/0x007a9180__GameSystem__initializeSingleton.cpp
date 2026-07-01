// FUNC_NAME: GameSystem::initializeSingleton
// Function at 0x007a9180: Singleton initialization for a game system.
// Allocates a 0x40-byte object, initializes it with three parameters, and registers it.
void __thiscall GameSystem::initializeSingleton(uint32_t param1, uint32_t param2, uint32_t param3)
{
    int objPtr;

    // Check and set global singleton flag
    if (DAT_0112b188 == 0) {
        DAT_0112b188 = 1;

        // Allocate memory for the singleton object (0x40 bytes)
        objPtr = allocMemory(0x40);
        if (objPtr != 0) {
            objPtr = constructObject(param1);  // Initialize object using param1
        }

        // Store param2 and param3 at offsets 0x38 and 0x3c from object base
        *(uint32_t *)(objPtr + 0x38) = param2;
        *(uint32_t *)(objPtr + 0x3C) = param3;

        // Final registration/post-initialization
        registerObject(objPtr);
    }
    return;
}