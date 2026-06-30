// FUNC_NAME: Array8::computeCountAndCall
void Array8::computeCountAndCall(void) const {
    // Read two integer fields at offsets +0x8 and +0xC (likely m_bufferStart and m_bufferEnd as byte offsets)
    // Compute element count: (end - start) / 8 (each element is 8 bytes)
    int elementCount = (*(int *)(this + 8) - *(int *)(this + 0xC)) >> 3;
    // Pass the count to another processing function
    FUN_006364d0(elementCount);
}