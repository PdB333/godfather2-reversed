// FUNC_NAME: EntityManager::findIndexByKey
int __thiscall EntityManager::findIndexByKey(int this, int key, uint *outIndex)
{
    uint index = 0;
    // +0x24: count of elements in the managed array
    if (*(int *)(this + 0x24) == 0) {
        return 0;
    }
    do {
        // Check if the element at current index matches the key
        if (FUN_004d4b70(key) == 0) {
            *outIndex = index;
            return 1;
        }
        index++;
    } while (index < *(uint *)(this + 0x24));
    return 0;
}