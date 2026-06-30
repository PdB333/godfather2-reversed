// FUNC_NAME: EntryManager::findAndTrigger
// Address: 0x00729980
// Role: Searches an array of entries (3-int structs) for a matching ID and triggers a callback.

class EntryManager {
    // +0x00 .. +0x0F: unknown fields
    // +0x10: pointer to array of Entry structures (each 12 bytes)
    // +0x14: number of entries in the array

    struct Entry {
        int id;         // +0x00
        int data1;      // +0x04
        int data2;      // +0x08
    };

    uint entryCount;    // offset 0x14
    Entry* entries;     // offset 0x10

public:
    // __thiscall
    void findAndTrigger(int targetId) {
        for (uint i = 0; i < entryCount; i++) {
            if (entries[i].id == targetId) {
                // Guard against index overflow (likely compiler artifact)
                if (i != 0xFFFFFFFF) {
                    this->triggerEntry();  // calls FUN_007296e0
                }
                return;
            }
        }
    }

private:
    void triggerEntry(); // FUN_007296e0 – processes the matched entry
};