// FUNC_NAME: DynamicArray::reserve
// Function address: 0x005effe0
// Reconstructed C++ for DynamicArray::reserve (__thiscall)
// This function grows the capacity of a dynamic array of int (or 4-byte elements).
// Structure layout:
// +0x00: int* m_data (pointer to element array)
// +0x04: int m_size (number of elements currently stored)
// +0x08: int m_capacity (allocated capacity, elements are 4 bytes each)

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    int* oldData;
    uint copyCount;
    int* newData;

    if (this->m_capacity < newCapacity) {
        // Allocate new memory block (4 bytes per element)
        newData = (int*)EARSAlloc(newCapacity * 4);
        if (this->m_data != 0) {
            copyCount = 0;
            // Copy existing elements if any
            if (this->m_size != 0) {
                do {
                    if (newData != 0) {
                        newData[copyCount] = this->m_data[copyCount];
                    }
                    copyCount = copyCount + 1;
                } while (copyCount < (uint)this->m_size);
            }
            // Free old memory
            EARSFree(this->m_data);
        }
        // Update pointer and capacity
        this->m_data = newData;
        this->m_capacity = newCapacity;
    }
}