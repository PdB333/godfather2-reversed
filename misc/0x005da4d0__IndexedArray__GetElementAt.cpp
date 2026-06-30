// FUNC_NAME: IndexedArray::GetElementAt
int* IndexedArray::GetElementAt(int* outputRef, int index)
{
    // this points to an IndexedArray struct:
    // +0x00: int* bufferDesc (pointer to buffer descriptor)
    // +0x04: int baseOffset (byte offset within buffer for first element)

    int* bufferDesc = *(int**)this;          // dereference this, get bufferDesc pointer
    int baseOffset = *(int*)(this + 4);      // get baseOffset

    if (bufferDesc == 0) {
        FUN_00b97aea(); // assert/crash: null buffer descriptor
    }

    // Each element is 0x28 (40) bytes
    uint elementOffset = baseOffset + index * 0x28;

    // Buffer descriptor layout (pointed to by bufferDesc):
    // +0x00: unknown (8 bytes)
    // +0x08: start (valid range start)
    // +0x0C: end (valid range end, exclusive top?)
    if (elementOffset > *(uint*)(bufferDesc + 0xC) || 
        elementOffset < *(uint*)(bufferDesc + 0x8)) {
        FUN_00b97aea(); // assert/crash: out of bounds
    }

    // Fill output reference: pointer to buffer descriptor and computed element offset
    outputRef[0] = (int)bufferDesc;
    outputRef[1] = elementOffset;

    return outputRef;
}