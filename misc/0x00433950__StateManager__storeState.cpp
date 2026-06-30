// FUNC_NAME: StateManager::storeState
void StateManager::storeState(int* pSourceData)
{
    // this in EDI
    int count = *(int*)((char*)this + 0x34);      // +0x34: number of elements
    if (count == 0) return;

    int* pArrayBase = *(int**)((char*)this + 0x50); // +0x50: pointer to element array

    for (unsigned int i = 0; i < (unsigned int)count; ++i)
    {
        int* pElement = (int*)((char*)pArrayBase + i * 0xB0); // each element 0xB0 bytes
        // Copy 4 ints (16 bytes) into the element at offset 0xA0
        pElement[0x28] = pSourceData[0]; // +0xA0 / 4 = 0x28
        pElement[0x29] = pSourceData[1]; // +0xA4
        pElement[0x2A] = pSourceData[2]; // +0xA8
        pElement[0x2B] = pSourceData[3]; // +0xAC

        extern void onStateStoreCallback(void); // FUN_004338a0
        onStateStoreCallback();
    }
}