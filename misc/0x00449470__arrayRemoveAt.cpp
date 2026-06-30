// FUNC_NAME: arrayRemoveAt
// Removes an element at the given index from a simple dynamic array (base pointer + size).
// The array stores 8-byte elements (two 32-bit values).
// Parameters are passed via __fastcall: index in ECX, array descriptor in EDX.
void __fastcall arrayRemoveAt(unsigned int index, int *array)
{
    // array[0] = pointer to element data (8 bytes per element)
    // array[1] = current number of elements
    int *data = (int *)array[0];
    int size = array[1];

    // Shift all subsequent elements left by one slot, unless index is the last element
    if (index < size - 1U) {
        do {
            // Copy the two dwords of element (index+1) over element index
            int *dest = data + index * 2;              // base + index * 8 bytes
            int *src  = data + (index + 1) * 2;        // base + (index+1) * 8 bytes
            *dest     = *src;                          // first dword
            *(dest + 1) = *(src + 1);                  // second dword
            index++;
        } while (index < size - 1U);
    }

    // Decrement element count
    array[1] = size - 1;
}