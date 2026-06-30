// FUNC_NAME: ObjectManager::releaseEntries

class ObjectManager {
public:
    // Structure for each entry (8 bytes)
    struct Entry {
        int m_ptr;       // offset 0x0: pointer to object data (+0xc from allocation base)
        int m_unknown;   // offset 0x4: unused?
    };

    // +0x74: pointer to dynamic array of Entry
    Entry* m_pEntries;
    // +0x78: number of entries
    int m_nEntryCount;

    // Release all active entries and then perform final cleanup
    void releaseEntries() {
        unsigned int idx = 0;
        if (m_nEntryCount != 0) {
            do {
                int ptrVal = m_pEntries[idx].m_ptr;
                // Skip null or sentinel (0x48) entries
                if ((ptrVal != 0) && (ptrVal != 0x48)) {
                    // Adjust pointer back by 0xc to get allocation base and free it
                    freeMemoryBlock((void*)(ptrVal - 0xc));
                }
                idx++;
            } while (idx < m_nEntryCount);
        }
        finalCleanup(); // FUN_006bccd0
    }
};

// External helper functions
void freeMemoryBlock(void* pBlock);  // FUN_004088c0
void finalCleanup();                 // FUN_006bccd0