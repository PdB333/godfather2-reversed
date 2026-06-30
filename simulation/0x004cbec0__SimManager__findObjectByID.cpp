// FUNC_NAME: SimManager::findObjectByID
// Function address: 0x004cbec0
// Finds an object in an internal container by comparing an ID at offset 0x6c.
// Container structure: this+8 points to a struct with count at +4 and array of pointers at +8.
// Returns pointer to object, or 0 if not found.

int SimManager::findObjectByID(int id)
{
    // Pointer to container stored at this+0x8
    ContainerHeader *container = *(ContainerHeader **)(this + 8);
    if (container == nullptr) {
        return 0;
    }

    // Linear search through container's object array
    for (uint i = 0; i < container->count; i++) {
        int *objectPtr = container->objects[i];
        // Compare ID field at object+0x6c
        if (*(int *)(objectPtr + 0x6c) == id) {
            return (int)objectPtr; // Return pointer to found object
        }
    }
    return 0;
}