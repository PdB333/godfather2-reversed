// FUNC_NAME: CEntryManager::createEntry
void __thiscall CEntryManager::createEntry(void* param_2, void* param_3) {
    // Check global system activation (FUN_00481660)
    if (!FUN_00481660()) {
        return;
    }

    // Allocate 0x40 byte block (FUN_009c8e50)
    void* newEntry = FUN_009c8e50(0x40);
    if (newEntry == nullptr) {
        return;
    }

    // Initialize entry (likely sets vtable or base fields)
    FUN_008db7a0(newEntry);

    // Store the two user-provided pointers at offsets +0x38 and +0x3c
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(newEntry) + 0x38) = param_2;
    *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(newEntry) + 0x3c) = param_3;

    // Register the entry with the manager (FUN_00481690)
    FUN_00481690(newEntry);
}