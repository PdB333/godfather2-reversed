// FUNC_NAME: SlotManager::getEntryById
// Address: 0x005f8300
// Reconstructed from Ghidra decompilation for The Godfather 2 (EARS engine, x86)
// This function resolves a given ID into an entry in a two-level table system.
// A slot (index 0-255) is obtained from an internal allocator; if successful,
// the corresponding subtable is indexed to find the entry. The entry’s first two
// dwords are zeroed and the slot index is stored at offset 0xB.
// On failure, an error flag (0x84) is set at this+0x38 and null is returned.

struct Entry {
    uint32_t field0;   // +0x00
    uint32_t field4;   // +0x04
    uint8_t  pad[3];   // +0x08..0x0A
    uint8_t  slotIndex; // +0x0B
};

struct SlotEntry {          // size 0xC
    int*    dataPtr;        // +0x00 – points to a header containing base at +0x20
    int     unknown4;       // +0x04 – unused here
    Entry*  entries;        // +0x08 – base of entry array for this slot
};

Entry* __thiscall SlotManager::getEntryById(int id) {
    byte slotIdx = FUN_005f6710();  // returns 0xFF if no free slot
    if (slotIdx != 0xFF) {
        SlotEntry* slot = (SlotEntry*)(*(int*)(this + 0x24) + slotIdx * 0xC);
        int offset = (id - *(int*)(*slot->dataPtr + 0x20)) / 0x24; // stride 0x24
        Entry* entry = slot->entries + offset; // entry stride is 0xC
        entry->field0 = 0;
        entry->field4 = 0;
        entry->slotIndex = slotIdx;
        return entry;
    }
    *(uint32_t*)(this + 0x38) |= 0x84;  // mark allocation failure
    return nullptr;
}