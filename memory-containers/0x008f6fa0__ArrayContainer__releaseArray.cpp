// FUNC_NAME: ArrayContainer::releaseArray
// Function address: 0x008f6fa0
// Role: Destructor for a dynamic array of 16-byte entries, each containing a pointer to an object.
// Frees each object via a deallocation function, then frees the array memory itself.
struct ArrayContainer {
    void** m_pArray;  // +0x00: pointer to array of entries (each 16 bytes)
    int m_iCount;     // +0x04: number of entries

    void releaseArray() {
        int index = m_iCount - 1;
        if (index >= 0) {
            int offset = index * 16; // each entry is 16 bytes
            do {
                void* pObject = *(void**)((char*)m_pArray + offset);
                if (pObject != 0) {
                    FUN_009c8f10(pObject); // release each object
                }
                index--;
                offset -= 16;
            } while (index >= 0);
        }
        if (m_pArray != 0) {
            FUN_009c8f10(m_pArray); // release the array itself
        }
    }
};