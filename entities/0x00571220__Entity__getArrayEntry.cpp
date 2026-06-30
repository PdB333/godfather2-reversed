// FUNC_NAME: Entity::getArrayEntry
// Function at 0x00571220
// Retrieves a pointer to an element from an array container.
// this+0x70: pointer to container structure (size unknown)
// this+0x76: short index into the array
// container+0x18: count of elements (int)
// container+0x1C: pointer to array (each element 0x18 bytes)
// Returns pointer to element or 0 if invalid.

int Entity::getArrayEntry()
{
    // Get container pointer
    int* container = *(int**)(this + 0x70);
    if (container != nullptr)
    {
        int count = *(int*)(container + 0x18);
        void* array = *(void**)(container + 0x1C);
        if (count > 0 && array != nullptr)
        {
            short index = *(short*)(this + 0x76);
            if (index >= 0 && index < count)
            {
                // Return pointer to element (each 0x18 bytes)
                return (int)((char*)array + index * 0x18);
            }
        }
    }
    return 0;
}