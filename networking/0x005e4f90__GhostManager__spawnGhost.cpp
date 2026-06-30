// FUNC_NAME: GhostManager::spawnGhost
// Function at 0x005e4f90: Creates a new ghost/replicated object via vtable call.
// Returns handle (0 on failure). Input: typeId (non-zero) and userData.
// Uses global factory vtable at DAT_01223510 for polymorphic creation.

bool GhostManager::spawnGhost(int typeId, int userData) {
    int outTypeId = 0;
    int outUserData = 0;

    // Validate this pointer, typeId, and computed base offset
    if ((this != nullptr) && (typeId != 0) &&
        (int *basePtr = *(int *)((char *)this + 0x10) + (int)this; basePtr != nullptr) &&
        (this != (GhostManager *)-0x18))
    {
        // Retrieve object info from some manager
        if (getObjectInfo(&outTypeId, &outUserData) != false) {
            int newHandle = generateNewHandle();

            // Allocate memory for new object (32 bytes)
            void *memory = operator new(0x20);
            if (memory != nullptr) {
                // Construct the object using type-specific constructor
                void *constructed = constructObject(outTypeId);
                if (constructed != nullptr) {
                    outTypeId = (int)constructed;
                    // Cast global vtable and call virtual creation (slot 0x10)
                    int (**vtable)(void *, int, int, int, void *, int) = *(int (***)(void *, int, int, int, void *, int))DAT_01223510;
                    bool success = vtable[0x10 / 4](basePtr, *(int *)((char *)this + 0xC), *(int *)((char *)this + 0x14), outUserData, (void *)constructed, userData);
                    if (success != false) {
                        destroyObject(&outTypeId);
                        return newHandle;
                    }
                    operator delete(constructed);
                }
            }
        }
    }
    return 0;
}