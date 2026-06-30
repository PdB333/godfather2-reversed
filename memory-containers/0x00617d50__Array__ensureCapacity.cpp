// FUNC_NAME: Array::ensureCapacity
// Function address: 0x00617d50
// Description: Grows the internal array to hold at least 'newCapacity' elements.
// Each element is 8 bytes (two 4-byte fields). Layout: +0x00 data ptr, +0x04 size, +0x08 capacity.
//
// Note: The allocator FUN_009c8e80 and free FUN_009c8f10 are likely operator new/delete.
// The caller FUN_00617a80 uses this function to manage a dynamic array of pairs.

void __thiscall Array::ensureCapacity(uint newCapacity)
{
    // unaff_ESI holds 'this' pointer.
    if (this->m_capacity < newCapacity)
    {
        // Allocate new buffer: newCapacity * 8 bytes per element.
        int* newData = (int*)FUN_009c8e80(newCapacity * 8);  // e.g., operator new

        if (this->m_data != (int*)0x0)
        {
            uint copyIndex = 0;
            int* dest = newData;

            if (this->m_size != 0)
            {
                do {
                    if (dest != (int*)0x0)
                    {
                        int* src = this->m_data;
                        // Copy each 8-byte pair (two ints)
                        dest[0] = src[copyIndex * 2];
                        dest[1] = src[copyIndex * 2 + 1];
                    }
                    copyIndex++;
                    dest += 2;  // advance by two ints (8 bytes)
                } while (copyIndex < (uint)this->m_size);
            }

            // Free the old buffer
            FUN_009c8f10(this->m_data);  // e.g., operator delete
        }

        this->m_data = newData;
        this->m_capacity = newCapacity;
    }
}