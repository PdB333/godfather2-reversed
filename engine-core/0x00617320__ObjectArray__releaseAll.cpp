// FUNC_NAME: ObjectArray::releaseAll

extern void* g_MemoryManager;               // DAT_01205964 - pointer to memory manager vtable
extern void __cdecl releaseObject(void* obj); // FUN_00616dc0
extern void __cdecl freeArray(void* ptr);     // FUN_009c8f10

class ObjectArray {
public:
    // Offset +0x00: pointer to array of 8-byte entries
    struct ArrayEntry {
        uint32_t padding;  // 4 bytes (unused)
        void*    pObject;  // 4 bytes – pointer to the ref-counted object
    };
    ArrayEntry* m_pEntries; // +0x00
    int         m_count;    // +0x04

    void __thiscall releaseAll() {
        int i;
        for (i = m_count - 1; i >= 0; i--) {
            // Each entry is 8 bytes, object pointer at offset +4 within the entry
            ArrayEntry& entry = m_pEntries[i];
            void* obj = entry.pObject;
            if (obj != nullptr) {
                // Decrement reference count at offset +0x08 in the object
                short* refCount = reinterpret_cast<short*>((char*)obj + 8);
                (*refCount)--;
                if (*refCount == 0) {
                    // Object's last reference gone – cleanup and delete
                    releaseObject(obj);
                    // Call virtual destructor via memory manager vtable (offset 4)
                    void* vtable = *reinterpret_cast<void**>(g_MemoryManager);
                    void (*destructor)(void*, int) = reinterpret_cast<void (*)(void*, int)>(
                        *reinterpret_cast<int*>(vtable) + 4
                    );
                    destructor(obj, 0);
                }
                // Clear the entry’s object pointer
                entry.pObject = nullptr;
            }
        }
        if (m_pEntries != nullptr) {
            freeArray(m_pEntries);
        }
    }
};