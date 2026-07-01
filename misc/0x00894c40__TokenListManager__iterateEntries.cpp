// FUNC_NAME: TokenListManager::iterateEntries
void __thiscall TokenListManager::iterateEntries(uint param2, uint param3) {
    // +0x2c: pointer to some data (e.g., list container)
    // +0x34: flags byte (bit 2 = disabled flag)
    if (this->pData != nullptr && !(this->flags & 0x02)) {
        // Get a list associated with param2 (key/index)
        TokenList* list = (TokenList*)FUN_00893500(param2); // e.g., getListForKey
        if (list != nullptr) {
            // +0x04: first entry pointer in the list
            ushort* entry = list->firstEntry;
            if (entry != nullptr) {
                // Call a functor on each entry; stops when functor returns false (0)
                bool keepGoing = FUN_008948a0(entry, param3); // e.g., processEntry
                while (keepGoing) {
                    // Advance by the entry's total size (size includes the 2-byte length field)
                    entry = (ushort*)((char*)entry + *entry);
                    keepGoing = FUN_008948a0(entry, param3);
                }
            }
        }
    }
}