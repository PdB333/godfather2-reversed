// FUNC_NAME: HandleList::clearAll

typedef void (*FreeFunc)(void*);
extern FreeFunc g_freeFunc; // DAT_01206694

struct ListEntry {
    int field_0;       // +0x00: unknown
    void* pItem;       // +0x04: pointer to allocated item (with 16-byte header)
};

// Each entry in the list has a header with an index at offset -8 and the actual allocation at offset -16.
// The manager (stored at this+0x1e38) holds:
//   +0x04: count of active handle allocations
//   +0x0C: pointer to an array of pointers (handles), indexed by the index stored in the header
// When freeing, we clear the handle and decrement the count, then call g_freeFunc on the original allocation.

void HandleList::clearAll() {
    // Get the number of items from the ushort at +0x10
    ushort count = *(ushort*)(this + 0x10);
    if (count != 0) {
        uint idx = count;
        while (idx > 0) {
            idx--;
            // Array at +0x14 is a pointer to an array of ListEntry (8 bytes each)
            ListEntry* entries = *(ListEntry**)(this + 0x14);
            void* pItem = entries[idx].pItem;
            if (pItem != 0) {
                // Manager pointer at +0x1e38
                int* manager = *(int**)(this + 0x1e38);
                // Read the index from the item's header (at offset -8)
                int handleIdx = *(int*)((char*)pItem - 8);
                // Clear the corresponding handle in the manager's handle array
                int** handleArray = (int**)(*(int*)((char*)manager + 0x0C));
                handleArray[handleIdx] = 0;
                // Decrement the manager's handle count
                int* handleCount = (int*)((char*)manager + 4);
                (*handleCount)--;
                // Free the actual allocation (header is 16 bytes before pItem)
                g_freeFunc((char*)pItem - 0x10);
            }
        }

        // Now free the array itself (same pattern)
        ListEntry* arrayPtr = *(ListEntry**)(this + 0x14);
        if (arrayPtr != 0) {
            int* manager = *(int**)(this + 0x1e38);
            int handleIdx = *(int*)((char*)arrayPtr - 8);
            int** handleArray = (int**)(*(int*)((char*)manager + 0x0C));
            handleArray[handleIdx] = 0;
            int* handleCount = (int*)((char*)manager + 4);
            (*handleCount)--;
            g_freeFunc((char*)arrayPtr - 0x10);
        }

        // Reset the count
        *(ushort*)(this + 0x10) = 0;
    }
}