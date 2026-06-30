// FUNC_NAME: TrackedObjectManager::removeObject
// Address: 0x006bcea0
// Removes an object from two parallel containers:
// - m_objectList (simple pointer array at +0x5c, count at +0x60)
// - m_keyValueMap (array of 8-byte key-value pairs at +0x68, count at +0x6c)
// Uses swap-with-last removal pattern for efficiency. The key-value map is
// searched via a helper function that likely returns the index for a given key.

void __thiscall TrackedObjectManager::removeObject(void* thisPtr, void* objectToRemove)
{
    // m_objectList: array of pointers
    int* objectList = *(int**)((char*)thisPtr + 0x5c);
    int objectCount = *(int*)((char*)thisPtr + 0x60);
    
    // Search for objectToRemove in the object list by pointer equality
    for (int i = 0; i < objectCount; i++)
    {
        if (objectList[i] == (int)objectToRemove)
        {
            // Found — if not the last element, swap with the last one
            if (i != objectCount - 1)
            {
                objectList[i] = objectList[objectCount - 1];
            }
            // Decrement count (effectively remove)
            *(int*)((char*)thisPtr + 0x60) = objectCount - 1;
            return; // Object removed, no further action needed
        }
    }
    
    // Not found in object list — try the key-value map
    int mapIndex = FUN_006bcb20(objectToRemove); // Get index in map (returns -1 if not found)
    if (mapIndex >= 0)
    {
        // m_keyValueMap: array of 8-byte entries (int key + int value)
        int* keyValueArray = *(int**)((char*)thisPtr + 0x68);
        int mapCount = *(int*)((char*)thisPtr + 0x6c);
        
        // If not the last entry, swap with last
        if (mapIndex != mapCount - 1)
        {
            keyValueArray[mapIndex * 2]     = keyValueArray[(mapCount - 1) * 2];
            keyValueArray[mapIndex * 2 + 1] = keyValueArray[(mapCount - 1) * 2 + 1];
        }
        // Decrement count
        *(int*)((char*)thisPtr + 0x6c) = mapCount - 1;
    }
}