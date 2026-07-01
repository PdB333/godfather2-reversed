// FUNC_NAME: DynamicArray::init
void __thiscall DynamicArray::init(int param_2, int param_3)
{
    // Allocate a 12-byte header block
    int* header = (int*)heapAllocate(12);
    if (header != nullptr) {
        // Allocate the primary data array: (capacity + 1) * 4 bytes
        int* dataArray = (int*)heapAllocateArray((param_2 + 1) * 4);
        header[2] = (int)dataArray; // store pointer at header offset +8
    }
    this->m_pHeader = header;          // +0x00
    this->m_count = 0;                 // +0x04
    this->m_capacity = param_2;        // +0x08
    this->m_someFlag = param_3;        // +0x0C
    this->m_unknown = 0;               // +0x10

    // Zero-initialize the primary data array
    for (uint i = 0; i <= param_2; i++) {
        ((int*)header[2])[i] = 0;
    }

    // Allocate a secondary array of same size
    this->m_pSecondaryArray = (int*)heapAllocateArray((param_2 + 1) * 4); // +0x14
}