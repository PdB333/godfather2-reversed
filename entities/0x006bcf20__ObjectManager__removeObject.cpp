//FUNC_NAME: ObjectManager::removeObject
// Function address: 0x006bcf20
// Removes an object from the managed list, given a pointer to the object.
// The object must have a valid flag at offset 0x1f58 (bit 0x15).
// If found, the last element in the array is moved to the removed slot, count decremented,
// then lock/unlock on the container handle, and finally release the object.
// If not found, an error is logged.

void __thiscall ObjectManager::removeObject(int thisPtr, int objectPtr)
{
    int index;
    int count;
    int arrayPtr;
    int containerHandle;

    // Check if the object's valid flag (bit 21) is set
    if ((*(uint *)(objectPtr + 0x1f58) >> 0x15 & 1) != 0) {
        index = findIndex(objectPtr); // FUN_006bcb60 - returns index of object in array
        if (index >= 0) {
            count = *(int *)(thisPtr + 0x6c); // current number of elements
            if (index != count - 1) {
                // Move last element to the removed slot (fast removal, order not preserved)
                arrayPtr = *(int *)(thisPtr + 0x68); // pointer to array of 8-byte entries
                *(undefined4 *)(arrayPtr + index * 8) = *(undefined4 *)(arrayPtr + (count - 1) * 8);
                *(undefined4 *)(arrayPtr + index * 8 + 4) = *(undefined4 *)(arrayPtr + (count - 1) * 8 + 4);
            }
            // Decrement count
            *(int *)(thisPtr + 0x6c) = count - 1;

            // Lock/unlock on container handle (likely a mutex or reference counter)
            containerHandle = *(int *)(thisPtr + 0x54);
            lock(containerHandle);   // FUN_007351c0
            unlock(containerHandle); // FUN_00790d30

            // Release the object
            releaseObject(objectPtr); // FUN_006bda80
            return;
        }
        // Object not found in list - log error
        logError(objectPtr + 0x3c); // FUN_004088c0
    }
    return;
}