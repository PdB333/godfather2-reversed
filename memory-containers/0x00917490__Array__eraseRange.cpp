// FUNC_NAME: Array::eraseRange
// Address: 0x00917490
// Role: Remove a range of elements from a dynamic array (pointer at +0x00, size at +0x04).
// Parameters: this->data (int*), this->count (int)
//             startIndex (int, inclusive), endIndex (int, exclusive)
// Erases elements from startIndex to endIndex-1, shifting remaining elements left.
void __thiscall Array::eraseRange(int startIndex, int endIndex)
{
    if (endIndex - startIndex == 0) return; // nothing to remove

    int newCount = this->count - (endIndex - startIndex);
    int* source = this->data + endIndex;
    int* dest   = this->data + startIndex;

    // Only copy if there are elements after the removed range
    if (startIndex < newCount)
    {
        int elementsToCopy = newCount - startIndex;
        do {
            *dest = *source;
            source++;
            dest++;
            elementsToCopy--;
        } while (elementsToCopy != 0);
    }

    this->count = newCount;
}