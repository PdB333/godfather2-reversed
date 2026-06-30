// FUNC_NAME: ObjectiveManager::processActiveEntries
void __thiscall ObjectiveManager::processActiveEntries(void)
{
    // +0x00: state field (2 = inactive/closed)
    if (this->state == 2) {
        return;
    }
    // +0x28 -> count of entries (uint at offset 0xA0)
    if (this->entryCount == 0) {
        return;
    }
    // +0x29 -> pointer to array of Entry structs (each 0x1C bytes)
    Entry* entries = this->entries;
    for (uint i = 0; i < this->entryCount; i++) {
        Entry& entry = entries[i];
        // Entry has two pointers: +0x00 -> outer object (with status at +0xB2)
        // +0x04 -> inner object (the target of the call)
        if ((*(byte*)(entry.outer + 0xB2) & 1) == 0) {
            continue;
        }
        int inner = entry.inner;
        // inner object fields: +0x04 active flag (byte) == 1
        // +0x06 some flag (byte) != 0
        // +0x08 flags (byte) & 0x10 must be 0
        if (*(byte*)(inner + 4) != 1) continue;
        if (*(byte*)(inner + 6) == 0) continue;
        if (*(byte*)(inner + 8) & 0x10) continue;
        // Process this inner object (likely marking as done/clearing)
        FUN_00459b30(inner, 0);
    }
}