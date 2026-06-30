// FUNC_NAME: IndexedArray::getEntryValue (0x00604e20)

class IndexedArray {
public:
    // Entry structure: size 0xC
    struct Entry {
        /* +0x00 */ int m_id;          // possibly ID or key
        /* +0x04 */ int m_value;       // the value we're getting
        /* +0x08 */ int m_unknown;     // unused in this function
    };

    // Offset 0x08: pointer to array of Entry objects
    /* +0x08 */ Entry* m_pEntries;    

    // Get the value field from the entry at index param_2
    // param_2: index into the array (0-based)
    int getEntryValue(int index) const {
        return m_pEntries[index].m_value;
    }
};