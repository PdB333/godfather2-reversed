// FUNC_NAME: removeFromFixedArray
void __fastcall removeFromFixedArray(unsigned int index, int *arrayHeader)
{
    // arrayHeader[0] : pointer to base of array (each element 8 bytes)
    // arrayHeader[1] : current number of elements in array
    int count = arrayHeader[1];
    
    // Only shift if the index is before the last element
    if (index < count - 1) {
        unsigned int *base = (unsigned int *)arrayHeader[0];
        do {
            // Copy the next element (8 bytes) over the current position
            unsigned int *src = base + (index + 1) * 2;   // each element is 2 ints
            unsigned int *dst = base + index * 2;
            dst[0] = src[0];
            dst[1] = src[1];
            index++;
        } while (index < count - 1);
    }
    // Reduce element count
    arrayHeader[1] = count - 1;
}