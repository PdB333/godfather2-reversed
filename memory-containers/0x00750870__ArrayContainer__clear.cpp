// FUNC_NAME: ArrayContainer::clear
void __fastcall ArrayContainer::clear(int *thisPtr)
{
    // this layout: +0x00 = pointer to array of 12-byte elements, +0x04 = element count
    int *arrayBuffer = (int *)thisPtr[0];
    int elemCount = thisPtr[1];
    int idx = elemCount - 1;
    if (-1 < idx) {
        int offset = idx * 12; // 0xC bytes per element
        do {
            // Check if the first word of the element (likely a pointer/flag) is non-zero
            if (*(int *)((int)arrayBuffer + offset) != 0) {
                // Destroy the element at this address
                destroyElement((void *)((int)arrayBuffer + offset));
            }
            idx = idx + -1;
            offset = offset + -0xc;
        } while (-1 < idx);
    }
    if (arrayBuffer != 0) {
        freeArrayBuffer(arrayBuffer);
    }
}