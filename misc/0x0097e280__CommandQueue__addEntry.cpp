// FUNC_NAME: CommandQueue::addEntry
// Address: 0x0097e280
// Role: Adds a new entry to a dynamic array of 16-byte entries, reallocating if needed.
// The entry is zeroed, then initialized with a unique ID from FUN_00950b20 and a global value.

struct CommandEntry {
    uint64_t data0; // +0x00
    uint64_t data1; // +0x08
    uint32_t param; // +0x10 (actually offset 0xC within the 16-byte block)
};

class CommandQueue {
public:
    // +0xC0: pointer to array of CommandEntry
    // +0xC4: current count of entries
    // +0xC8: capacity (allocated size)
    void addEntry(uint32_t param2);
};

void __thiscall CommandQueue::addEntry(uint32_t param2) {
    int capacity = *(int *)(this + 0xC8); // +0xC8: capacity
    int count = *(int *)(this + 0xC4);    // +0xC4: current count

    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Reallocate the array to new capacity
        FUN_0097bd80(capacity);
    }

    count = *(int *)(this + 0xC4);
    *(int *)(this + 0xC4) = count + 1;

    CommandEntry* entry = (CommandEntry*)(count * 0x10 + *(int *)(this + 0xC0));
    entry->data0 = 0;
    entry->data1 = 0;

    int uniqueId = FUN_00950b20();
    if (uniqueId != 0) {
        FUN_0097c010(entry, uniqueId, _DAT_00d8fd74, 0x4bbd6cc6);
    }

    entry->param = param2; // +0x0C within the entry
    return;
}