// FUNC_NAME: ObjectArray::remove
// Address: 0x0084a8b0
// Role: Removes a pointer element from a dynamic array by swapping with the last element,
//       then decrements the reference count of the removed object (if the refcount field is non‑zero).

class ObjectArray {
public:
    void** m_pData; // +0x04
    int    m_nSize; // +0x08

    void remove(void* pItem);
};

void __thiscall ObjectArray::remove(void* pItem)
{
    int count = m_nSize;          // +0x08
    int i = 0;
    int foundIndex = -1;

    if (count != 0) {
        void** data = m_pData;    // +0x04
        do {
            foundIndex = i;
            if (data[i] == pItem)
                break;
            i++;
            foundIndex = -1;
        } while (i < count);
    }

    // If found and not the last element, replace with last
    if (foundIndex != count - 1) {
        m_pData[foundIndex] = m_pData[count - 1];
    }

    m_nSize = count - 1;

    // Release the removed item if it has a non‑zero reference count (field +0x40)
    if (*(int*)((char*)pItem + 0x40) != 0) {
        // Calls FUN_0084a730 – likely decrementRefCount/release
        releaseObject(pItem);
    }
}