// FUNC_NAME: Container::releaseAll
// Address: 0x008165e0
// Role: Destroys all elements in a container and frees the element array.

// Element size = 0x18 bytes
struct Element {
    int     field_0;       // +0x00
    void*   pObject;       // +0x08
    int     field_0x0C;    // +0x0C
    void    (*pfnDestructor)(void*); // +0x14
};

// Container structure:
// +0x00: Element* m_pElements
// +0x04: int      m_nCount
void __thiscall Container::releaseAll(int* thisPtr) {
    int count = thisPtr[1] - 1; // m_nCount - 1
    if (count >= 0) {
        Element* pElem = reinterpret_cast<Element*>(thisPtr[0]) + count;
        do {
            if (pElem->pObject != nullptr) {
                pElem->pfnDestructor(pElem->pObject);
            }
            count--;
            pElem--;
        } while (count >= 0);
    }

    if (thisPtr[0] != 0) {
        // Free the element array (likely operator delete[] or Memory::deallocate)
        FUN_009c8f10(thisPtr[0]);
    }
}