// FUNC_NAME: copyDynamicArrayWithSync
void copyDynamicArrayWithSync(void* thisPtr, DynamicArray* destArray, DynamicArray* srcArray, SyncObject* syncObject, int operationMode)
{
    // Handle special operation modes (1 and 2) - likely reference release operations
    if (operationMode == 1 || operationMode == 2)
    {
        syncFunction(srcArray); // Decrements refcount or releases the source array
        return;
    }

    // Acquire lock or increment refcount on syncObject at offset 0x9c (e.g., a mutex)
    syncFunction(reinterpret_cast<uint8_t*>(syncObject) + 0x9c);

    // Copy elements from srcArray to destArray, growing destArray if needed
    unsigned int copyCount = 0;
    if (srcArray->size != 0)
    {
        do {
            // Check if destArray is full
            if (destArray->size == destArray->capacity)
            {
                // Grow capacity: double or set to 1 if currently 0
                int newCapacity = (destArray->capacity == 0) ? 1 : destArray->capacity * 2;
                reallocateArray(newCapacity); // Presumably grows internal buffer to newCapacity elements
            }

            // Append element from srcArray to destArray
            int* destSlot = destArray->data + destArray->size;
            destArray->size++;
            if (destSlot != nullptr)
            {
                *destSlot = *(srcArray->data + copyCount);
            }
            copyCount++;
        } while (copyCount < static_cast<unsigned int>(srcArray->size));
    }

    // Release the lock or decrement refcount at offset 0x84
    syncFunction(reinterpret_cast<uint8_t*>(syncObject) + 0x84);
}