// FUNC_NAME: EntityDepthList::hasMatchingDescendant
// Address: 0x00586c00
// This function iterates over an internal list of depth values (12‑byte entries).  
// For each entry, it traverses a singly‑linked list starting from pRootEntity  
// (using offset 0x124 as the link pointer) by the number of steps stored in the entry.  
// If the resulting node exists and passes the predicate, the function returns 1.

// Predicate function (FUN_00586c90) takes a node and the parameter param_3
typedef int (__thiscall *EntityFilterFunc)(void* node, int param);

// Assumed structure for entries in the list (12 bytes each)
struct DepthEntry {
    int depth;         // +0x00: number of steps to follow in the linked list
    int unused_04;     // +0x04: not used here
    int unused_08;     // +0x08: not used here
};

// The class that owns this method is expected to have two fields at offsets 0 and 4:
//   int   m_count;         // number of entries
//   void* m_entriesArray;  // pointer to array of DepthEntry (each 0xC bytes)
int __thiscall EntityDepthList::hasMatchingDescendant(void* thisPtr, void* pRootEntity, int predicateParam) {
    int count = *(int*)thisPtr;                              // number of entries in the list
    byte* entries = *(byte**)((char*)thisPtr + 4);           // pointer to first DepthEntry

    for (int i = 0; i < count; ++i) {
        DepthEntry* entry = (DepthEntry*)(entries + i * 0xC);
        int depth = entry->depth;                            // number of steps to traverse

        // Only consider entries with valid root and non‑negative depth
        if (pRootEntity != 0 && depth >= 0) {
            // Start from the first node in the linked list (offset 0x124 from root)
            void* currentNode = *(void**)((char*)pRootEntity + 0x124);
            int steps = 0;
            while (steps < depth) {
                currentNode = *(void**)((char*)currentNode + 0x124);
                if (currentNode == 0) {
                    goto skipEntry;                          // chain ended prematurely
                }
                ++steps;
            }

            if (currentNode != 0) {
                // Apply predicate; if true, we have a match
                int result = ((EntityFilterFunc)0x00586c90)(currentNode, predicateParam);
                if (result != 0) {
                    return 1;
                }
            }
        }
skipEntry:
        continue;
    }
    return 0;
}