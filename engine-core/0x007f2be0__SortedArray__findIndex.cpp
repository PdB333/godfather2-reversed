//FUNC_NAME: SortedArray::findIndex
// Function address: 0x007f2be0
// Binary search on a sorted array of 20-byte structures with a 4-uint32 key.
// The array is sorted lexicographically by the four uint32 fields.
// Returns the index of the matching element, or -1 if not found.

struct SortedArrayElement {
    uint32_t key0;   // +0x00
    uint32_t key1;   // +0x04
    uint32_t key2;   // +0x08
    uint32_t key3;   // +0x0C
    uint32_t extra;  // +0x10 (padding or additional data, total size 0x14)
};

class SortedArray {
public:
    SortedArrayElement* m_pElements; // +0x00
    int m_nCount;                    // +0x04

    int findIndex(const uint32_t* key) const {
        int low = -1;
        int high = m_nCount;
        while (low + 1 != high) {
            int mid = (low + high) >> 1;
            SortedArrayElement* elem = &m_pElements[mid];
            if (elem->key0 < key[0]) {
                low = mid;
            } else if (elem->key0 > key[0]) {
                high = mid;
            } else {
                // key0 equal
                if (elem->key1 < key[1]) {
                    low = mid;
                } else if (elem->key1 > key[1]) {
                    high = mid;
                } else {
                    // key1 equal
                    if (elem->key2 < key[2]) {
                        low = mid;
                    } else if (elem->key2 > key[2]) {
                        high = mid;
                    } else {
                        // key2 equal
                        if (elem->key3 < key[3]) {
                            low = mid;
                        } else {
                            high = mid;
                        }
                    }
                }
            }
        }
        if (high < m_nCount) {
            SortedArrayElement* elem = &m_pElements[high];
            if (elem->key0 == key[0] && elem->key1 == key[1] &&
                elem->key2 == key[2] && elem->key3 == key[3]) {
                return high;
            }
        }
        return -1;
    }
};