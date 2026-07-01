// FUNC_NAME: GrowingArray::resize (likely EARS container)
// Function address: 0x0095e8f0
// Resizes the array to `newCount` elements.
// If shrinking, destroys elements from the end using stored destructor function pointers.
// If growing, allocates additional memory and zero-initializes new elements.

// Structure of the array container (first two fields)
struct GrowingArray {
    void* pData;      // +0x00: pointer to array of Element (each 0x20 bytes)
    uint  count;      // +0x04: current element count
};

// Each element is 0x20 bytes with two pointer-and-destructor pairs
struct Element {
    void* m_ptr0;     // +0x00: data pointer
    void* m_ptr4;     // +0x04
    void* m_ptr8;     // +0x08
    void* m_dtor1;    // +0x0C: destructor function pointer for m_ptr0
    void* m_ptr10;    // +0x10: data pointer
    void* m_ptr14;    // +0x14
    void* m_ptr18;    // +0x18
    void* m_dtor2;    // +0x1C: destructor function pointer for m_ptr10
};

// External function to grow the underlying buffer (likely realloc or allocate)
void __stdcall ensureArrayCapacity(uint newCount); // FUN_0095e090

void __thiscall resize(GrowingArray* this, uint newCount) {
    uint oldCount = this->count; // +0x04

    if (oldCount < newCount) {
        // Need to grow
        ensureArrayCapacity(newCount);
        oldCount = this->count; // re-read after possible reallocation

        if (oldCount < newCount) {
            // There are new slots to zero-initialize
            int byteOffset = oldCount * 0x20; // each element is 0x20 bytes
            uint numNew = newCount - oldCount;

            Element* base = (Element*)this->pData; // +0x00
            Element* newStart = (Element*)((uintptr_t)base + byteOffset);

            for (uint i = 0; i < numNew; i++) {
                // Zero out the entire new element (8 DWORDs)
                newStart[i].m_ptr0  = 0;
                newStart[i].m_ptr4  = 0;
                newStart[i].m_ptr8  = 0;
                newStart[i].m_dtor1 = 0;
                newStart[i].m_ptr10 = 0;
                newStart[i].m_ptr14 = 0;
                newStart[i].m_ptr18 = 0;
                newStart[i].m_dtor2 = 0;
            }

            this->count = newCount;
            return;
        }
    } else if (oldCount > newCount) {
        // Shrinking: destroy elements from the end
        int lastIndex = (int)oldCount - 1;
        if ((int)newCount <= lastIndex) {
            int byteOffset = lastIndex * 0x20; // start from last element
            int numRemove = lastIndex - (int)newCount + 1;

            Element* base = (Element*)this->pData; // +0x00
            for (int i = 0; i < numRemove; i++) {
                Element* elem = (Element*)((uintptr_t)base + byteOffset);

                // Destroy second pointer (m_ptr10) if non-null
                if (elem->m_ptr10 != 0) {
                    void (*destructor2)(void*) = (void (*)(void*))elem->m_dtor2; // +0x1C
                    destructor2(elem->m_ptr10);
                }

                // Destroy first pointer (m_ptr0) if non-null
                if (elem->m_ptr0 != 0) {
                    void (*destructor1)(void*) = (void (*)(void*))elem->m_dtor1; // +0x0C
                    destructor1(elem->m_ptr0);
                }

                byteOffset -= 0x20; // move to previous element
            }
        }

        this->count = newCount;
    }
    // else oldCount == newCount: nothing to do
    return;
}