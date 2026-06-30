// FUNC_NAME: GameObjectManager::getObject
// Address: 0x004c3f10
// Role: Returns a pointer to the object at the index stored in this+0x76
// The data source (array metadata) is stored at this+0x70.
// Array metadata: +0x18 = count, +0x1c = pointer to element array (each element 0x18 bytes).

void* __thiscall GameObjectManager::getObject()
{
    // Pointer to the array metadata block (owns the actual array)
    ArrayMetadata* metadata = *(ArrayMetadata**)(this + 0x70);
    if (metadata == nullptr)
        return nullptr;

    // Bounds check: count at +0x18 must be > 0, array at +0x1c must be non-null
    int count = *(int*)(metadata + 0x18);
    int* array = *(int**)(metadata + 0x1c);
    if (count <= 0 || array == nullptr)
        return nullptr;

    // Index stored as short at this+0x76
    short index = *(short*)(this + 0x76);
    if (index < 0 || index >= count)
        return nullptr;

    // Each element is 0x18 bytes
    return (void*)(array + index * 0x18);
}