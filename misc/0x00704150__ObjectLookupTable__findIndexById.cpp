// FUNC_NAME: ObjectLookupTable::findIndexById

class ObjectLookupTable {
public:
    // Performs a linear search over an array of entry pairs.
    // Each entry consists of two integers (stored consecutively in memory).
    // The first integer of each pair represents an encoded ID; when non-zero,
    // subtract 0x48 to obtain the actual ID. Zero is treated as ID 0.
    // The second integer is ignored in this lookup.
    // Returns the index of the entry whose ID matches targetId, or -1 if not found.
    int __thiscall findIndexById(int targetId) {
        int index = -1;
        if (m_entryCount != 0) {
            int* entriesPtr = m_pEntries;   // +0x00
            index = 0;
            while (true) {
                int rawValue = *entriesPtr;
                int actualId;
                if (rawValue == 0) {
                    actualId = 0;
                } else {
                    actualId = rawValue - 0x48; // Decode ID by subtracting 0x48
                }
                if (actualId == targetId) {
                    break;
                }
                index++;
                entriesPtr += 2; // Advance to next entry pair
                if (index == m_entryCount) {
                    return -1;
                }
            }
        }
        return index;
    }

private:
    int* m_pEntries;   // +0x00: Pointer to array of entry pairs
    int m_entryCount;  // +0x04: Number of entries in the table
};