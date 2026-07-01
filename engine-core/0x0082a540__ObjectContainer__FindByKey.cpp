// FUNC_NAME: ObjectContainer::FindByKey
// Address: 0x0082a540
// Searches a dynamic array container for an object whose 128-bit key (four 32-bit fields at offsets +0x1c, +0x20, +0x24, +0x28) matches the given key array.
// Returns pointer to found object (as int), or 0 if not found.
// Container: pointer to array of object pointers at +0x08, count at +0x0c.

int __thiscall ObjectContainer::FindByKey(int* key)
{
    uint count = *(uint*)(this + 0xc);          // number of elements
    int** ptr = *(int***)(this + 0x8);          // pointer to array of object pointers

    for (uint i = 0; i < count; i++)
    {
        int* object = ptr[i];
        if (*(int*)(object + 0x1c) == key[0] &&
            *(int*)(object + 0x20) == key[1] &&
            *(int*)(object + 0x24) == key[2] &&
            *(int*)(object + 0x28) == key[3])
        {
            return (int)object;
        }
    }
    return 0;
}