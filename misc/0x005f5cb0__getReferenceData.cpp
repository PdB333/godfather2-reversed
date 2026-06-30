// FUNC_NAME: getReferenceData
// Address: 0x005f5cb0
// Role: Extracts a pointer and data from a reference node. Returns data with low byte forced to 1 if pointer is non-null.
// The node structure is expected to have at least three ints: [0]=pointer, [2]=data (type/flags).
uint32_t __thiscall getReferenceData(const int* pNode, int* outPointer, int* outData) {
    int ptr = pNode[0];             // +0x00: pointer to object
    *outPointer = ptr;

    if (ptr != 0) {
        int data = pNode[2];        // +0x08: associated data (type/refcount/flag)
        *outData = data;
        // Clear low byte and set it to 1 (indicates valid reference)
        return (data & 0xFFFFFF00) | 1;
    }

    *outData = 0;
    return 0;
}