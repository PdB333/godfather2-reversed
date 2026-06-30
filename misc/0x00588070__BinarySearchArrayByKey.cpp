// FUNC_NAME: BinarySearchArrayByKey
// Address: 0x00588070
// Description: Binary search on a sorted array of pointers to structures.
//   Each structure has a key field at offset 0x14 or 0x1c depending on flags at +0x2c and first int at +0x00.
//   The array size is passed in EDI (added as third parameter for reconstruction).
//   Returns pointer to the array element containing the found pointer, or 0 if not found.
//   If multiple entries share the same key, returns the first one (lowest index).

typedef struct {
    int     field0;         // +0x00: some type/ID
    /* ... other fields ... */
    int     field5;         // +0x14: key (alternative)
    /* ... */
    int     field7;         // +0x1c: key (alternative)
    /* ... */
    uint8_t flags;          // +0x2c: flags byte (bit 0x20 controls key selection)
} SearchObject;

SearchObject** __fastcall binarySearchArrayByKey(SearchObject** array, int targetKey, int arraySize)
{
    int low = 0;
    int high = arraySize;
    int mid;
    SearchObject* obj;
    int key;
    int resultIdx;

    // Binary search for targetKey
    while (low < high) {
        mid = (high + low) >> 1;
        obj = array[mid];
        // Determine which field holds the key
        if (((obj->flags & 0x20) == 0) || (obj->field0 < 2)) {
            key = obj->field5;
        } else {
            key = obj->field7;
        }
        if (key < targetKey) {
            low = mid + 1;
            high = high;
        } else {
            high = mid;
        }
    }

    // If found, move to first occurrence (if duplicates exist)
    if (low < arraySize) {
        obj = array[low];
        if (((obj->flags & 0x20) == 0) || (obj->field0 < 2)) {
            key = obj->field5;
        } else {
            key = obj->field7;
        }
        if (key == targetKey) {
            // Scan backward for first occurrence
            while (low > 0) {
                SearchObject* prev = array[low - 1];
                int prevKey;
                if (((prev->flags & 0x20) == 0) || (prev->field0 < 2)) {
                    prevKey = prev->field5;
                } else {
                    prevKey = prev->field7;
                }
                if (prevKey != targetKey) break;
                low--;
            }
            return &array[low];  // pointer to the element in the array
        }
    }
    return 0;
}