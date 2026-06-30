// FUNC_NAME: EntityManager::binarySearchByKey
// Address: 0x00587c60
// Role: Binary search in a sorted array of GameObject pointers by ID (key).
// The array is sorted by a primary ID key, but some objects have a secondary ID
// selected by a flag at offset 0x2C (bit 0x20) and a fallback condition (first int < 2).
// Returns pointer to the first matching slot in the array, or nullptr if not found.

struct GameObject {
    int primaryId;      // +0x00
    int secondaryId;    // +0x04
    // ... other fields ...
    unsigned char flags; // +0x2C (bit 0x20: use secondaryId if set and primaryId >= 2)
};

// Search sorted array of pointers for object matching key.
// count: number of elements (passed in EDI register at this call site)
// Returns address of the array slot containing the matching pointer, or nullptr.
GameObject** findGameObjectByKey(GameObject** array, int key, int count) {
    int low = 0;
    int high = count;
    int mid;

    while (low < high) {
        mid = (low + high) >> 1;
        GameObject* obj = array[mid];
        int objKey;

        // Determine which key to compare: primary or secondary based on flag and condition.
        if ((obj->flags & 0x20) == 0 || obj->primaryId < 2) {
            objKey = obj->primaryId;
        } else {
            objKey = obj->secondaryId;
        }

        if (objKey < key) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (low < count) {
        GameObject* obj = array[low];
        int objKey;

        if ((obj->flags & 0x20) == 0 || obj->primaryId < 2) {
            objKey = obj->primaryId;
        } else {
            objKey = obj->secondaryId;
        }

        if (objKey == key) {
            // Scan backwards to first occurrence in case of duplicates
            while (low > 0) {
                GameObject* prev = array[low - 1];
                int prevKey;

                if ((prev->flags & 0x20) == 0 || prev->primaryId < 2) {
                    prevKey = prev->primaryId;
                } else {
                    prevKey = prev->secondaryId;
                }

                if (prevKey != key) break;
                low--;
            }
            return &array[low];
        }
    }

    return nullptr;
}