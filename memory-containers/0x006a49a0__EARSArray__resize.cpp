// FUNC_NAME: EARSArray::resize
// Address: 0x006a49a0
// Role: Resize an array of 0x30-byte elements with debug fill and vtable management

#include <cstdint>

extern void* g_pElementVtable;   // PTR_LAB_00d5d708
extern void* g_pDestroyedVtable; // PTR_LAB_00e2f0c0
extern void  FUN_006a4790(int newSize); // reallocation helper

// Element is 48 bytes (0x30), with magic numbers and a vtable at offset 0x24 (9th uint32)
struct Element {
    uint32_t debugMarkers[4]; // offsets 0x00, 0x04, 0x08, 0x0C
    // ... other fields (20 bytes) ...
    void* m_vtable; // offset 0x24
};

// EARSArray: simple dynamic array container
struct EARSArray {
    Element* m_pData; // +0x00: pointer to element buffer
    int      m_nSize; // +0x04: current element count

    void resize(int newSize);
};

void EARSArray::resize(int newSize) {
    int oldSize = m_nSize;

    if (oldSize < newSize) {
        // Grow array
        FUN_006a4790(newSize);
        oldSize = m_nSize; // size may have changed after realloc

        if (oldSize < newSize) {
            int byteOffset = oldSize * sizeof(Element);
            int count = newSize - oldSize;

            do {
                Element* elem = reinterpret_cast<Element*>(
                    reinterpret_cast<char*>(m_pData) + byteOffset);

                if (elem != nullptr) {
                    // Debug fill pattern (EA standard)
                    elem->debugMarkers[0] = 0xBADBADBA;
                    elem->debugMarkers[1] = 0xBEEFBEEF;
                    elem->debugMarkers[2] = 0xEAC15A55;
                    elem->debugMarkers[3] = 0x91100911;
                    elem->m_vtable = &g_pElementVtable;
                }

                byteOffset += sizeof(Element);
                count--;
            } while (count != 0);

            m_nSize = newSize;
            return;
        }
    } else {
        if (oldSize == newSize)
            return;

        // Shrink array: mark removed elements as destroyed
        int lastIndex = oldSize - 1;
        if (newSize <= lastIndex) {
            int byteOffset = lastIndex * sizeof(Element);
            int count = (lastIndex - newSize) + 1;

            do {
                Element* elem = reinterpret_cast<Element*>(
                    reinterpret_cast<char*>(m_pData) + byteOffset);

                elem->m_vtable = &g_pDestroyedVtable;

                byteOffset -= sizeof(Element);
                count--;
            } while (count != 0);
        }
    }

    m_nSize = newSize;
}