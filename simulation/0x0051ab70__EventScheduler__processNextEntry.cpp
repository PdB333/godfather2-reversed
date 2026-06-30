// FUNC_NAME: EventScheduler::processNextEntry
// Function at 0x0051ab70 – processes a queue of objects starting from m_currentIndex+1.
// Each entry (0x14 bytes) contains a pointer to a class instance and a flags field at offset 0x10.
// The previous entry's flags (bit 5) must be set to continue; then a vtable call at +0x30 is made
// on the current entry's object. Returns early if the call returns true.
// Parameter: param_2 is passed to the virtual method.

class EventScheduler {
    // Structure: each entry 0x14 bytes
    // +0x00: int* pObject (pointer to an object with vtable at *pObject)
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: unknown
    // +0x10: int flags (byte at offset 0x10 is checked for bit 5)
    struct Entry {
        void* pObject;       // +0x00
        int field_4;          // +0x04
        int field_8;          // +0x08
        int field_C;          // +0x0C
        int flags;            // +0x10
    };

    short m_currentIndex;   // +0x80? Actually passed as in_EAX, likely a member
    short m_entryCount;     // +0x80? But short* at param_1+0x80 – could be array count
    Entry m_entries[1];     // +0xf4? Flexible array at offset 0xf4

public:
    void processNextEntry(int param_2) {
        int idx = m_currentIndex + 1;
        if (idx >= m_entryCount) return;

        Entry* entry = reinterpret_cast<Entry*>(reinterpret_cast<char*>(this) + 0xf4) + idx;
        do {
            // Check bit 5 of previous entry's flags
            if (!(entry[-1].flags & 0x20)) {
                return;
            }
            if (entry->pObject != nullptr) {
                // Get vtable pointer from object
                void* vtable = *reinterpret_cast<void**>(entry->pObject);
                // Virtual function at offset 0x30 (12th entry if four-byte pointers)
                bool (__thiscall* func)(void*, int) = reinterpret_cast<bool (__thiscall*)(void*, int)>(vtable + 0x30);
                if (func(entry->pObject, param_2)) {
                    return;
                }
            }
            idx++;
            entry++;
        } while (idx < m_entryCount);
    }
};