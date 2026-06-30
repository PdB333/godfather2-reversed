// FUNC_NAME: CEventManager::dispatchToGroup

// Address: 0x004C2C40
// This function iterates over an array of entries, each containing an ID and a list of listener objects.
// If an entry with a matching ID is found, it calls a callback (vtable+0x28) on each listener in that entry's list.
// The callback is likely a method pointer stored in the vtable (offset 0x28) that takes a single void* argument.

class CEventManager {
public:
    // Structure for each entry in the array (size 12 bytes)
    struct Entry {
        int m_id;       // +0x00: ID to match
        void** m_list;  // +0x04: pointer to array of listener pointers
        int m_count;    // +0x08: number of listeners in the array
    };

private:
    // Offset 0x82: pointer to array of Entry structures
    Entry* m_pEntries;
    // Offset 0x83: number of entries in the array
    int m_numEntries;
    // Note: The vtable pointer is at offset 0 of the object.
    // Vtable offset 0x28 holds a function pointer: void (*callback)(void*);

public:
    // __thiscall
    int dispatchToGroup(int groupId) {
        Entry* it = m_pEntries;
        Entry* end = it + m_numEntries;

        if (it == end) {
            return 1; // No entries, return success
        }

        do {
            Entry* entry = (Entry*)*it; // it points to an int*, but Entry is cast from the pointer stored there
            // Actually the array elements are pointers to Entry, so we dereference to get the Entry pointer.
            // In the assembly: piVar2 = (int *)*piVar3;
            // So we treat piVar3 as a pointer to an array of int* (each int* is a pointer to an Entry)
            // So we need to cast it as: Entry** pEntryArray = (Entry**)m_pEntries; then *pEntryArray gives an Entry*.
            // But the decompiler used piVar3 as int* and then *piVar3 as int* which is Entry*.

            Entry* entryPtr = (Entry*)*it; // Actually it is an int* pointing to the array element (which is an int*)
            // To be clear: m_pEntries is a pointer to an array of int (each int is a pointer to Entry)
            // So we need to cast it as Entry** and then iterate.

            if (entryPtr->m_id == groupId) {
                unsigned int i = 0;
                if (entryPtr->m_count != 0) {
                    do {
                        // Call the callback for each listener in the list
                        // The callback is at vtable offset 0x28 (function pointer taking a void* argument)
                        void* listener = entryPtr->m_list[i];
                        (*(void(*)(void*))(*(int*)this + 0x28))(listener);
                        i++;
                    } while (i < (unsigned int)entryPtr->m_count);
                }
                return 1; // Success
            }
            it++;
        } while (it != end);

        return 1; // Success even if no matching entry found
    }
};