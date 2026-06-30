// FUNC_NAME: lookupIdInTable
// Function at 0x004f1330: Binary search in a sorted array of 8-byte entries (4-byte key, 4-byte value)
// Globals: DAT_01218f2c = count of entries, DAT_01218f28 = pointer to array of {uint key, uint value}
uint lookupIdInTable(uint key)
{
    int low = 0;
    int high = DAT_01218f2c - 1; // last valid index
    if (high < 0) {
        return 0; // empty table
    }

    do {
        int mid = (low + high) >> 1; // compute midpoint
        uint entryKey = *(uint *)(DAT_01218f28 + mid * 8); // each entry is 8 bytes
        if (key < entryKey) {
            high = mid - 1;
        } else if (key <= entryKey) {
            // key == entryKey, found
            return *(uint *)(DAT_01218f28 + 4 + mid * 8); // return value (second 4 bytes)
        } else {
            low = mid + 1;
        }
    } while (low <= high);

    return 0; // not found
}