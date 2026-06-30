// FUNC_NAME: RefCountedArray::clearAll
void RefCountedArray::clearAll()
{
    int count = m_nCount; // param_1[1]
    if (count != 0) {
        while (count--, count >= 0) {
            Entry* entry = &m_pEntries[count]; // Each entry is 8 bytes (two ints)
            void* pObject = entry->pObject;    // entry->pObject is at offset +4
            if (pObject != nullptr) {
                // Decrement reference count at pObject->refCount (short at +8)
                short* refCount = reinterpret_cast<short*>(reinterpret_cast<char*>(pObject) + 8);
                *refCount = *refCount - 1;
                if (*refCount == 0) {
                    // Release the object (cleanup/decouple)
                    releaseObject(pObject); // FUN_00616dc0
                    // Call memory deallocator via global vtable (DAT_01205964)
                    // The vtable at offset 4 is the free function
                    typedef void (__thiscall *FreeFunc)(void*, int);
                    FreeFunc freeFunc = reinterpret_cast<FreeFunc>(*reinterpret_cast<int*>(*reinterpret_cast<int*>(DAT_01205964) + 4));
                    freeFunc(pObject, 0);
                }
                // Clear the entry's object pointer
                entry->pObject = nullptr;
            }
        }
        m_nCount = 0;
    }
}