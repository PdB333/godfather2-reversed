// FUNC_NAME: CollectionManager::gatherItemsByCategory
// Function address: 0x006beed0
// Reconstructed from Ghidra decompilation of The Godfather 2 (2008, EARS engine)
// Purpose: Filters source array items by category, appends matches to destination array, then sorts

void __thiscall CollectionManager::gatherItemsByCategory(
    void* thisObject,
    DynamicArray* sourceArray,  // +0x0: data pointer, +0x4: size, +0x8: capacity (inferred)
    DynamicArray* destArray,    // +0x0: data pointer, +0x4: size, +0x8: capacity
    int targetCategory)
{
    int sourceSize = sourceArray->size;
    arrayEnsureCapacity(sourceSize);   // Ensures some internal buffer? Might be unrelated to source
    // This call may be a safety check or unrelated initialization; kept as-is.

    for (int i = 0; i < sourceSize; i++) {
        int item = *((int*)sourceArray->data + i);  // Retrieve item pointer/ID from source
        int itemCategory = getItemCategory();        // Returns category for current item? (global state)
        if (itemCategory == targetCategory) {
            // Ensure dest array has capacity for one more element
            if (destArray->size == destArray->capacity) {
                int newCapacity = (destArray->capacity == 0) ? 1 : destArray->capacity * 2;
                arrayEnsureCapacity(newCapacity);  // Reallocate dest array
            }
            // Append item to dest array
            int* destData = (int*)destArray->data;
            destData[destArray->size] = item;
            destArray->size++;
            // Notify that the collection changed
            notifyContentsChanged(thisObject);
        }
    }

    // Sort dest array if more than one element (comparator at 0x006be9c0)
    if (destArray->size > 1) {
        qsort(destArray->data, destArray->size, sizeof(int), compareInts);
    }
}