// FUNC_NAME: PriorityManager::setKeyPriority
// Function address: 0x008bcf90
// Updates or inserts a priority value associated with a 128-bit key.
// If the key exists, the priority is only raised (if new value is greater).
// Otherwise, a new entry is created with the given priority.

#include <cstring>

class PriorityManager {
public:
    // Sets the priority for the given key (array of 4 uint32).
    // Priority is only updated if the new value is higher than the stored one.
    void __thiscall setKeyPriority(uint32_t key[4], uint8_t priority);

private:
    // Returns index of the entry matching 'key', or -1 if not found.
    int __thiscall findIndexByKey(const uint32_t key[4]);

    // Adds a new entry to the internal array. 'entry' is a pointer to a 0x2c-byte structure.
    void __thiscall addEntry(const void* entry);

    // Internal data (offset +0x08): pointer to an array of Entry structures.
    // Each Entry is 0x2c bytes, with the priority byte at offset 0x28.
    struct Entry {
        uint64_t unknown0[3];   // +0x00, +0x08, +0x10
        uint32_t key[4];        // +0x18
        uint8_t priority;       // +0x28
        uint8_t padding;        // +0x29 (possibly flags or unused)
        // Total: 0x2c bytes
    };

    void* m_entries; // offset +0x08, pointer to array of Entry
};

void __thiscall PriorityManager::setKeyPriority(uint32_t key[4], uint8_t priority) {
    int index = findIndexByKey(key);
    if (index < 0) {
        // Key not found – create a new entry.
        Entry entry;
        std::memset(&entry, 0, sizeof(entry));
        entry.key[0] = key[0];
        entry.key[1] = key[1];
        entry.key[2] = key[2];
        entry.key[3] = key[3];
        entry.priority = priority;
        entry.padding = 0; // clear flags/extra byte
        addEntry(&entry);
    } else {
        // Key exists – update priority only if new value is higher.
        Entry* entries = static_cast<Entry*>(m_entries);
        if (entries[index].priority < priority) {
            entries[index].priority = priority;
        }
    }
}