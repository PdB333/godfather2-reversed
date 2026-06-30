// FUNC_NAME: PoolManager::removeThreeItemsFromPool
void PoolManager::removeThreeItemsFromPool(void)
{
    // Global base address for pool manager (DAT_0120669c)
    int* baseAddr = (int*)0x0120669c;
    // Pool container pointer at offset +0x1e38
    int* container = *(int**)(baseAddr + 0x1e38);

    // Three object pointers to remove (DAT_012066a0, DAT_012066a4, DAT_012066a8)
    int* objects[3];
    objects[0] = (int*)0x012066a0;
    objects[1] = (int*)0x012066a4;
    objects[2] = (int*)0x012066a8;

    // Destructor function pointer (DAT_01206694)
    void (*destructor)(int*) = (void (*)(int*))0x01206694;

    for (int i = 0; i < 3; ++i)
    {
        int* objPtr = objects[i];
        if (objPtr != 0)
        {
            // Header is 16 bytes before the object pointer
            int* header = objPtr - 4; // since objPtr is int*, subtract 4 ints = 16 bytes
            // Actually objPtr is a pointer, we need to subtract 0x10 bytes
            // So cast to char* then back:
            int* header = (int*)((char*)objPtr - 0x10);

            // Index stored at offset -8 from object
            int index = *(int*)((char*)objPtr - 8);

            // Array of object handles at container + 0xc
            int* handleArray = (int*)(container + 0x3); // +0xc = 3 ints
            handleArray[index] = 0; // Clear the slot

            // Decrement count at container + 0x4
            int* countPtr = container + 1; // +0x4 = 1 int
            *countPtr = *countPtr - 1;

            // Call destructor on header
            destructor(header);
        }
    }

    return;
}