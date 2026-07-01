// FUNC_NAME: Array8::pushBack
int* __fastcall Array8::pushBack(Array8* this) // returns pointer to new element (8 bytes each)
{
    // this->m_nCapacity at offset 0x08, this->m_nSize at 0x04, this->m_pData at 0x00
    int capacity = this->m_nCapacity;
    if (this->m_nSize == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Resize the underlying buffer to new capacity
        FUN_0084a270(capacity);
    }
    int index = this->m_nSize;      // current size
    this->m_nSize = index + 1;      // increment size
    return (int*)this->m_pData + index * 2; // each element is 8 bytes => index * 2 in int pointers
}