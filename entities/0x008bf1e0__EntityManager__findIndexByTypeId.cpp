// FUNC_NAME: EntityManager::findIndexByTypeId
uint __thiscall EntityManager::findIndexByTypeId(int typeId)
{
    uint index = 0;
    // +0x1a4: pointer to dynamic array of object pointers
    int** objectArray = reinterpret_cast<int**>(this + 0x1a4);
    // +0x1a8: count of objects in the array
    uint objectCount = *reinterpret_cast<uint*>(this + 0x1a8);

    if (objectCount != 0) {
        int** current = objectArray;
        do {
            // Each object has an ID/type field at offset +8 (int at index 2)
            int* objPtr = *current;
            if (objPtr[2] == typeId) {
                return index;
            }
            index++;
            current++;
        } while (index < objectCount);
    }
    return 0xFFFFFFFF; // not found
}