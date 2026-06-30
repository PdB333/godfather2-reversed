// FUNC_NAME: DynamicArray::growToAtLeast
// Address: 0x0054aee0
// This function ensures the dynamic array's capacity is at least newCapacity.
// It reallocates the internal buffer if needed, copying existing elements.
// Structure offsets:
//   +0x0: m_pData (int*) - pointer to element array
//   +0x4: m_size (int) - number of elements currently stored
//   +0x8: m_capacity (int) - allocated capacity (in elements)

void DynamicArray::growToAtLeast(uint newCapacity)
{
    // Only grow if current capacity is insufficient
    if (this->m_capacity < newCapacity) {
        // Allocate new buffer: each element is 4 bytes (int/pointer sized)
        int* newData = (int*)FUN_009c8e80(newCapacity * 4);  // likely operator new[] or malloc
        
        // Copy existing elements if there is any data stored
        if (this->m_pData != 0) {
            uint i = 0;
            int* dest = newData;
            if (this->m_size != 0) {
                do {
                    if (dest != 0) {
                        *dest = this->m_pData[i];  // element-wise copy
                    }
                    i++;
                    dest++;
                } while (i < (uint)this->m_size);
            }
            // Free old buffer
            FUN_009c8f10(this->m_pData);  // likely operator delete[] or free
        }
        
        // Update pointers and capacity
        this->m_pData = newData;
        this->m_capacity = newCapacity;
    }
    // If no growth needed, do nothing
}