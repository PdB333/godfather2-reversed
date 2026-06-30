// FUNC_NAME: ProcessManager::updateAllLists

// Reconstructed from Ghidra at 0x00596570
// This function processes three lists of objects, calling specific virtual functions on each.
// It is part of a manager that holds three categories of objects (e.g., tasks, timers, etc.)
// The flag at +0x4 indicates readiness; if false, it triggers a fatal error via global jump table.

struct ProcessManager {
    char m_bInitialized;     // +0x4
    int m_count1;            // +0x8
    int m_count2;            // +0xC
    int m_count3;            // +0x10
    void** m_array1;         // +0x14
    int* m_seq1;             // +0x18
    void** m_array2;         // +0x20
    int* m_seq2;             // +0x24
    void** m_array3;         // +0x2C
    int* m_seq3;             // +0x30
    int m_counter1;          // +0x1C
    int m_counter2;          // +0x28
    int m_counter3;          // +0x34
};

void __fastcall ProcessManager::updateAllLists(ProcessManager* this) {
    if (!this->m_bInitialized) {
        // Fatal error: manager not initialized
        // Jump table at DAT_01205590 is used to invoke error handler
        (**(code **)(*DAT_01205590 + 4))();
        return;
    }

    // Process first list (objects have a virtual function at offset 0x58)
    this->m_counter1 = 0;
    int idx1 = 0;
    if (this->m_count1 > 0) {
        do {
            // Call virtual function at vtable+0x58 (probably "update" or "process")
            void* obj = *(this->m_array1 + idx1);
            (**(code (**)(void))(**(int**)obj + 0x58))();
            idx1++;
            *(this->m_seq1 + idx1 - 1) = idx1;
        } while (idx1 < this->m_count1);
    }
    // Mark end of sequence for list1
    *(this->m_seq1 + idx1 - 1) = -1; // 0xFFFFFFFF

    // Process second list (objects have a virtual function at offset 0x08)
    this->m_counter2 = 0;
    int idx2 = 0;
    if (this->m_count2 > 0) {
        do {
            void* obj = *(this->m_array2 + idx2);
            (**(code (**)(void))(**(int**)obj + 0x08))();
            idx2++;
            *(this->m_seq2 + idx2 - 1) = idx2;
        } while (idx2 < this->m_count2);
    }
    *(this->m_seq2 + idx2 - 1) = -1;

    // Process third list (same format as second)
    this->m_counter3 = 0;
    int idx3 = 0;
    if (this->m_count3 > 0) {
        do {
            void* obj = *(this->m_array3 + idx3);
            (**(code (**)(void))(**(int**)obj + 0x08))();
            idx3++;
            *(this->m_seq3 + idx3 - 1) = idx3;
        } while (idx3 < this->m_count3);
    }
    *(this->m_seq3 + idx3 - 1) = -1;
}