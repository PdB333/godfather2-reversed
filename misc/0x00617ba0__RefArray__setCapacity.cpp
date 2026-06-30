// FUNC_NAME: RefArray::setCapacity
// Function address: 0x00617ba0
// Role: Grows the internal array of 8‑byte elements (key + ref‑counted object) to at least `newCapacity`.

// Assuming class layout:
// 0x00: int*  m_pData    – pointer to array of elements (each 8 bytes: 4‑byte key + 4‑byte pointer to ref object)
// 0x04: int   m_nCount   – number of currently used elements
// 0x08: int   m_nCapacity – allocated capacity (number of elements)

// Each ref‑counted object has a short refcount at offset +0x08 and a vtable at offset 0x00.
// The vtable's second entry (offset 0x04) is the virtual destructor.
// The global pointer DAT_01205964 points to a vtable (or static function table) used for destruction.

void RefArray::setCapacity(int* pThis, unsigned int newCapacity)
{
    // If the requested capacity is larger than the current one, reallocate
    if ((unsigned int)pThis[2] < newCapacity) {
        // Allocate new memory for the expanded array (8 bytes per element)
        int* newData = (int*)FUN_009c8e80(newCapacity * 8);

        if (*pThis != 0) {
            unsigned int i = 0;
            int* dst = newData;
            // Copy existing elements
            if (pThis[1] != 0) {
                do {
                    int* src = (int*)(*pThis + i * 8); // old element (key, pointer)
                    if (dst != (int*)0x0) {
                        *dst = *src;           // copy the key (first 4 bytes)
                        dst[1] = 0;            // clear the pointer (will be set by AddRef)
                        FUN_006164e0(dst + 1); // increment reference count / initialize
                    }
                    int* obj = (int*)src[1];
                    if (obj != (int*)0x0) {
                        // Decrement reference count (stored as short at offset 0x08)
                        *(short*)(obj + 8 / 4) = *(short*)(obj + 8 / 4) - 1;
                        if (*(short*)(obj + 8 / 4) == 0) {
                            FUN_00616dc0(obj);                       // internal cleanup
                            (**(code**)(*DAT_01205964 + 4))(obj, 0); // virtual destructor call
                        }
                        src[1] = 0;
                    }
                    i++;
                    dst += 2;
                } while (i < (unsigned int)pThis[1]);
            }
            FUN_009c8f10(*pThis); // free the old array
        }
        // Update the container fields
        *pThis = (int)newData;
        pThis[2] = (int)newCapacity; // note: newCapacity remains unsigned int, stored as int
    }
    return;
}