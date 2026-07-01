// FUNC_NAME: Vector::pushBack
// Address: 0x00906dc0
// Role: Push an element onto a dynamic array (vector) with resize if needed.
// Structure layout (32-bit):
//   +0x00: m_pData (int* pointer to element array)
//   +0x04: m_nSize (int count of elements)
//   +0x08: m_nCapacity (int allocated capacity)
// Element size: 4 bytes

void __thiscall Vector::pushBack(int *this, int *element) {
    int capacity = this[2];   // m_nCapacity
    int size = this[1];       // m_nSize

    if (size == capacity) {
        // Need to grow: if capacity is 0, start with 1; else double
        int newCapacity = (capacity == 0) ? 1 : (capacity * 2);
        // Call reallocate (FUN_00906bc0) - likely a static method or helper
        Vector::reserve(newCapacity);
        // Note: after reserve, this->m_nCapacity is updated; m_pData may change.
        // Re-read these values since they may have changed (but in the code they are used later)
        // However, the original code re-reads from this[1] and this[2] after the call.
        // But here we follow the original: capacity is not updated locally but it's fine.
    }

    // Store the element at the end
    int *dest = (int *)(this[0] + size * 4); // m_pData + size * sizeof(int)
    this[1] = size + 1;  // m_nSize++
    if (dest != nullptr) {
        *dest = *element;
    }
}