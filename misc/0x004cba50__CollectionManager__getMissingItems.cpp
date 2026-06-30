// FUNC_NAME: CollectionManager::getMissingItems
int* __thiscall CollectionManager::getMissingItems(void* this, int* outArray)
{
    // outArray is a growing array structure: [buffer, count, capacity]
    outArray[0] = 0;  // buffer pointer
    outArray[1] = 0;  // current count
    outArray[2] = 0;  // capacity

    // Get the singleton game manager
    int* gameManager = GameManager::getInstance();  // FUN_00ad8d40
    if (gameManager != nullptr)
    {
        // Get the collectible cache (virtual call at vtable+0x34)
        int* collectibleCache = reinterpret_cast<int*((*reinterpret_cast<int**>)(gameManager)[0x34 / 4])();
        if (collectibleCache != nullptr)
        {
            // Get the list of already collected items
            int* collectedList = reinterpret_cast<int*((*reinterpret_cast<int**>)(collectibleCache)[0x24 / 4])();

            // Get the number of items in our local list (this+0x0c)
            int localCount = *(int*)((char*)this + 0x0c);
            if (localCount > 0)
            {
                // Get the pointer to the local item ID array (this+0x14)
                int* localItems = *(int**)((char*)this + 0x14);

                // Get the count from the collected list (virtual call at vtable+0x3c, argument 0)
                int collectedCount = reinterpret_cast<int(*)(void*)>(*(int**)(collectedList + 0x3c / 4)?   // 0x3c offset in vtable
                                            (collectedList)[0x3c / 4](
                                                0);
                // Note: the virtual call at +0x3c returns the number of collected items.
                // The decompilation shows uVar4 receiving this value and later using it as both count and pointer.
                // We assume the collected list object has a method getCount() at vtable+0x3c.

                for (int i = 0; i < localCount; i++)
                {
                    int itemId = localItems[i];
                    bool found = false;

                    if (collectedCount > 0)
                    {
                        for (int j = 0; j < collectedCount; j++)
                        {
                            // Get the j-th collected item (virtual call at vtable+0x24)
                            int* collectedItem = reinterpret_cast<int*((*reinterpret_cast<int**>)(collectedList)[0x24 / 4])(j);

                            // Get the ID of the collected item (virtual call at vtable+0x0c)
                            int collectedItemId = reinterpret_cast<int(*)(void*)>(*(int**)(collectedItem + 0x0c / 4)? 
                                                      (collectedItem)[0x0c / 4]();

                            if (collectedItemId == itemId)
                            {
                                found = true;
                                break;
                            }
                        }
                    }

                    if (!found)
                    {
                        // Add item to output array (growing mechanism)
                        int count = outArray[1];
                        int capacity = outArray[2];
                        if (count == capacity)
                        {
                            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
                            // Reallocate logic (FUN_004cbc70) – assume it resizes the buffer
                            FUN_004cbc70(newCapacity);  // This likely expands the buffer
                            capacity = newCapacity;
                            outArray[2] = capacity;
                        }
                        outArray[1] = count + 1;
                        int* buffer = reinterpret_cast<int*>(outArray[0]);
                        buffer[count] = itemId;
                    }
                }
            }
        }
    }
    return outArray;
}