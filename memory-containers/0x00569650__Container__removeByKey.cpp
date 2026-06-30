// FUNC_NAME: Container::removeByKey
// Function address: 0x00569650
// Removes an entry from a fixed-size array (count at +0x120, keys at +0x20).
// The key to remove is taken from objWithKey at offset +0x110.
// Uses a global mutex for thread safety.

void Container::removeByKey(void *objWithKey)
{
    // Lock global mutex (DAT_00e2cbe8)
    MutexLock(&g_containerMutex); // FUN_00ab4db0

    uint count = *(uint *)((char *)this + 0x120); // element count
    uint index = 0;

    if (count != 0)
    {
        int targetKey = *(int *)((char *)objWithKey + 0x110); // key from argument

        // Search for the key in the array
        int *keys = (int *)((char *)this + 0x20); // start of key array
        while (keys[index] != targetKey)
        {
            index++;
            if (index >= count) // not found
            {
                MutexUnlock(&g_containerMutex); // FUN_00ab4e70
                return;
            }
        }

        // Found at index, remove by moving last element into this position
        if (index < count - 1)
        {
            keys[index] = keys[count - 1];
        }
        count--;
        *(uint *)((char *)this + 0x120) = count;
    }

    MutexUnlock(&g_containerMutex); // FUN_00ab4e70
}