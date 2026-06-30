// FUNC_NAME: FixedSizeArray::removeAt
void __fastcall FixedSizeArray::removeAt(int* this, unsigned int index)
{
    unsigned int count = this[1]; // m_nCount at +0x04
    if (index < count - 1) {
        int elementSize = 0x18; // 24 bytes per element
        int offset = index * elementSize; // byte offset of element to remove
        char* data = (char*)this[0]; // m_pData at +0x00
        do {
            // Shift element from index+1 down to index
            *(uint64_t*)(data + offset) = *(uint64_t*)(data + offset + 0x18);
            *(uint64_t*)(data + offset + 8) = *(uint64_t*)(data + offset + 0x18 + 8);
            *(uint64_t*)(data + offset + 16) = *(uint64_t*)(data + offset + 0x18 + 16);
            index++;
            offset += elementSize;
        } while (index < count - 1);
    }
    this[1] = count - 1; // decrement count
}