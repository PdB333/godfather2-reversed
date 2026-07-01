// FUNC_NAME: EARSArray::eraseRange
// Address: 0x00917760
// Removes a range of elements [startIndex, endIndex) from a dynamic array.
// The array structure: +0x00 = pointer to element data (int*), +0x04 = current size (int)
void __thiscall EARSArray::eraseRange(int startIndex, int endIndex)
{
    int rangeSize = endIndex - startIndex;
    if (rangeSize == 0) {
        return;
    }

    int newSize = this->size - rangeSize;               // +0x04
    int* src = this->data + endIndex;                   // +0x00
    int* dst = this->data + startIndex;

    // Number of elements to shift left after the removed range
    int elementsToShift = newSize - startIndex;
    if (startIndex < newSize) {
        for (int i = 0; i < elementsToShift; i++) {
            *dst++ = *src++;
        }
    }

    this->size = newSize;
}