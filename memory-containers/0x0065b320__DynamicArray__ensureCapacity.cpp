// FUNC_NAME: DynamicArray::ensureCapacity
void DynamicArray::ensureCapacity(uint requestedCount)
{
    // If current capacity is insufficient, reallocate
    if (g_capacity < requestedCount) {
        // Round requestedCount up to next multiple of 16 for alignment
        uint newCapacity = requestedCount + (0x10 - (requestedCount & 0xf));
        // Allocate new buffer: 12 bytes per element
        void* newData = malloc(newCapacity * 0xc);
        void* oldData = g_data;    // save old pointer

        // Set global to new buffer, then copy old contents
        g_data = newData;
        copyElements();             // copies from old to new using global count

        // Restore old pointer to free it, then update capacity and set new data
        g_data = oldData;
        free(oldData);
        g_capacity = newCapacity;
        g_data = newData;
    }
}