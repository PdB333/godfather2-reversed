// FUNC_NAME: ArrayContainer::clear

void __thiscall ArrayContainer::clear(ArrayContainer *this) {
    int count;
    int index;
    int offset;

    count = this->m_count - 1;
    if (count >= 0) {
        offset = count * 0x18;
        do {
            // Check if element is allocated (first 4 bytes of 0x18-sized element)
            if (*(int *)(this->m_pArray + offset) != 0) {
                // Destroy element at m_pArray + offset
                destroyElement(this->m_pArray + offset);  // FUN_004daf90
            }
            count--;
            offset -= 0x18;
        } while (count >= 0);
    }
    this->m_count = 0;
    // Free array memory
    operator delete(this->m_pArray);  // FUN_009c8f10
    this->m_pArray = nullptr;
    this->m_capacity = 0;
}