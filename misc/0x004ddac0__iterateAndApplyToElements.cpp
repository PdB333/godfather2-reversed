// FUNC_NAME: iterateAndApplyToElements
// Function address: 0x004ddac0
// Iterates over an array of 16-bit elements stored in a structure and calls a function on each element with a context parameter.
// The structure at param_1 contains: +0x00 pointer to array of uint16, +0x04 count of elements.

void iterateAndApplyToElements(ArrayHeader* array, int context)
{
    uint i = 0;
    if (array->count != 0) {
        do {
            applyToElement(*(uint16*)(array->elements + i * 2), context);
            i++;
        } while (i < (uint)array->count);
    }
    return;
}