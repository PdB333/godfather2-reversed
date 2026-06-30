// FUN_0043db90: SixIntKeyArray::findByKey
// Binary search for a record with a 6-int key in a sorted array.
// Class layout:
//   +0x00: int* m_arrayBase (pointer to array of 28-byte records)
//   +0x04: int m_count (number of elements)
// Element layout (size 0x1C = 28 bytes):
//   +0x00: int field0
//   +0x04: int field1
//   +0x08: int field2
//   +0x0C: int field3
//   +0x10: int field4
//   +0x14: int field5
//   remaining 4 bytes ignored for comparison (maybe padding or extra data)

class SixIntKeyArray {
public:
    int* m_arrayBase;
    int m_count;

    // Returns index of element matching key, or -1 if not found.
    // The array is sorted by the 6-field key (lexicographic?).
    int findByKey(const int* key) const;
};

int SixIntKeyArray::findByKey(const int* key) const {
    if (m_count == 0) {
        return -1;
    }

    int low = -1;
    int high = m_count;

    // binary search using a private comparison function
    while (low + 1 < high) {
        int mid = (low + high) >> 1; // integer mid
        if (compareByKey(mid)) {
            low = mid;
        } else {
            high = mid;
        }
    }

    // high is the candidate index; check exact match
    if (high < m_count) {
        int* element = m_arrayBase + high * 7; // 0x1C = 28 bytes = 7 ints
        if (element[0] == key[0] &&
            element[1] == key[1] &&
            element[2] == key[2] &&
            element[3] == key[3] &&
            element[4] == key[4] &&
            element[5] == key[5]) {
            return high;
        }
    }
    return -1;
}

// Private comparison: returns true if key > element at index.
// This uses a hidden member (maybe stored key) or global state.
// Actual implementation details unknown; stub provided.
bool SixIntKeyArray::compareByKey(int index) const {
    // Stub: compare key (set elsewhere) against m_arrayBase + index*7
    // For reconstruction, assume it returns (key > element at index)
}