// FUNC_NAME: ObjectManager::findIndexByID
// Function at 0x004420f0: Searches an array of 5-int structures for a matching ID, returns index or -1.
// __thiscall: this in ECX/EAX, but Ghidra shows in_EAX. Typically __thiscall passes 'this' in ECX, but here it's EA so maybe in EAX.
struct ObjectEntry {
    int id;          // +0x00: Unique identifier used for comparison
    int field4;      // +0x04
    int field8;      // +0x08
    int fieldC;      // +0x0C
    int field10;     // +0x10
};

class ObjectManager {
public:
    int m_objectCount;        // +0x28: Number of valid entries in the list
    ObjectEntry* m_pObjects;  // +0x24: Pointer to array of ObjectEntry[count]

    // Searches for an object by its ID. Returns index 0..(count-1) if found, -1 otherwise.
    int findIndexByID(int targetID)
    {
        if (m_objectCount <= 0) {
            return -1;
        }

        ObjectEntry* entry = m_pObjects;
        for (int i = 0; i < m_objectCount; ++i) {
            if (entry->id == targetID) {
                return i;
            }
            entry++; // Each ObjectEntry is sizeof(int)*5 = 20 bytes (5 ints)
        }
        return -1;
    }
};