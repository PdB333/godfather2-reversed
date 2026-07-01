// FUNC_NAME: ObjectManager::findObjectByID
int* __thiscall ObjectManager::findObjectByID(int* thisPtr, int objectID)
{
    // thisPtr points to an object that has a pointer to a data block at offset 0.
    // Data block layout:
    // +0x14: uint32_t count
    // +0x24: int** array (pointer to array of structures, each 0x34 bytes)
    int* dataBlock = (int*)*thisPtr;
    int** array = (int**)*(dataBlock + 0x24 / 4); // +0x24
    uint32_t count = *(uint32_t*)(dataBlock + 0x14 / 4); // +0x14

    for (uint32_t i = 0; i < count; i++)
    {
        // Each element is 13 ints (0x34 bytes). First int is the ID.
        if (*array[i] == objectID)
        {
            return array[i];
        }
    }
    return nullptr;
}