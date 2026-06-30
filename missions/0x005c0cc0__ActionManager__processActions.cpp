// FUNC_NAME: ActionManager::processActions

// Address: 0x005c0cc0
// Reconstructed C++ for processing a list of action entries.
// Each action entry (0xC bytes):
//   +0x00: function pointer (int (*)(void*, char, void*))
//   +0x04: first argument (void*)
//   +0x08: second argument (void*)
// Manager struct layout (this):
//   +0x00: ActionEntry* entries
//   +0x04: int count
//   +0x10: int currentIndex
//   +0x14: char flag (0 indicates just processed, 1 indicates advanced to new entry)
// Returns 1 if all actions processed, 0 if still in progress (call again).

int __thiscall ActionManager::processActions(void) {
    ActionEntry* entry;
    int result;
    int idx = this->currentIndex;

    // If index is beyond last entry, we're done
    if (this->count <= idx) {
        return 1;
    }

    entry = &this->entries[idx];
    result = (*entry->func)(entry->arg1, (char)this->flag, entry->arg2);
    this->flag = 0;  // Reset flag after processing

    if (result != 0) {
        this->currentIndex++;
        this->flag = 1;  // Mark that we advanced to a new entry
        if (this->currentIndex == this->count) {
            return 1;  // Reached end
        }
    }

    // Continue looping only if result == 2 (special repeat signal)
    while (result == 2) {
        idx = this->currentIndex;
        if (this->count <= idx) {
            return 1;
        }
        entry = &this->entries[idx];
        result = (*entry->func)(entry->arg1, (char)this->flag, entry->arg2);
        this->flag = 0;
        if (result != 0) {
            this->currentIndex++;
            this->flag = 1;
            if (this->currentIndex == this->count) {
                return 1;
            }
        }
    }

    return 0;  // Not done, need to be called again
}