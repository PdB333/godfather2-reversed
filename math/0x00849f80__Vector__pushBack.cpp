// FUNC_NAME: Vector::pushBack
// Function address: 0x00849f80
// Role: Add an element to the end of a dynamically-growing array (vector).
// Offsets: +0x10 = m_pBuffer (array of 32-bit elements), +0x14 = m_nCount, +0x18 = m_nCapacity

void __thiscall Vector::pushBack(int thisPtr, int element)
{
    int count = *(int *)(thisPtr + 0x14);
    int capacity = *(int *)(thisPtr + 0x18);

    if (count == capacity) {
        // Double capacity (or set to 1 if starting from 0)
        int newCapacity = (capacity != 0) ? (capacity * 2) : 1;
        FUN_00849880(newCapacity); // resize the internal buffer (likely realloc)
    }

    // Write element at the current end position
    int* pBuffer = *(int**)(thisPtr + 0x10);
    if (pBuffer != nullptr) {
        pBuffer[count] = element;
    }

    // Increment count
    *(int *)(thisPtr + 0x14) = count + 1;
}