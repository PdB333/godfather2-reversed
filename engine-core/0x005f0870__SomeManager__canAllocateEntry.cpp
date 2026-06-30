// FUNC_NAME: SomeManager::canAllocateEntry
bool __thiscall SomeManager::canAllocateEntry(void) {
    EntryNode* current = *(EntryNode**)(this + 8); // +0x08: head of linked list of entries
    while (current != nullptr &&
           (*(char*)(current + 8) == '\0' || !checkEntryCondition())) // +0x08: flag byte; +0x04: next pointer
    {
        current = *(EntryNode**)(current + 4);
    }
    return *(unsigned short*)(this + 0x12) < 35; // +0x12: count of used slots, max 35 (0x23)
}