// FUNC_NAME: Vector::reserve

void __thiscall Vector::reserve(uint newCapacity)
{
    int* newData;
    uint i;

    // If current capacity is insufficient, reallocate
    if (this->m_capacity < newCapacity) {
        // Allocate new buffer (4 bytes per element)
        newData = (int*)memAlloc(newCapacity * 4);

        // Copy existing elements from old buffer to new buffer
        if (this->m_pData != nullptr) {
            i = 0;
            if (this->m_size != 0) {
                do {
                    if (newData != nullptr) {
                        newData[i] = this->m_pData[i];
                    }
                    i++;
                } while (i < this->m_size);
            }

            // Free old buffer
            memFree(this->m_pData);
        }

        // Update pointer and capacity
        this->m_pData = newData;
        this->m_capacity = newCapacity;
    }
}