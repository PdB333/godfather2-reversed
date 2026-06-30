// FUNC_NAME: StringKeyedTable::findEntry
// Searches an array of 0x28-byte records for a match on a string key (param_1) and an int key (param_2).
// The array is stored as contiguous memory between this->pStart (+0x0C) and this->pEnd (+0x10).
// Each record: char name[32] at +0x00, int id at +0x20.
// Returns index if found (and record's id == param_2 or id < 0), else 0xFFFFFFFF.
int __thiscall StringKeyedTable::findEntry(byte *keyString, int keyId) {
    int count;
    if (*(int *)(this + 0x0C) == 0) {
        count = 0;
    } else {
        count = (*(int *)(this + 0x10) - *(int *)(this + 0x0C)) / 0x28;
    }
    if (count <= 0) return 0xFFFFFFFF;

    int index = 0;
    do {
        // Bounds check – if outside valid range, call error handler
        if (*(int *)(this + 0x0C) == 0 || (uint)index >= (uint)((*(int *)(this + 0x10) - *(int *)(this + 0x0C)) / 0x28)) {
            FUN_00b97aea(); // assertion/abort
        }
        byte *record = (byte *)(*(int *)(this + 0x0C) + index * 0x28);
        // Compare two-byte chunks (optimized strcmp)
        byte *pRecord = record;
        byte *pKey = keyString;
        int cmp;
        do {
            byte b1 = *pRecord;
            byte b2 = *pKey;
            bool less = b1 < b2;
            if (b1 != b2) {
                cmp = (1 - (int)less) - (int)(less != 0);
                goto check;
            }
            if (b1 == 0) break;
            b1 = pRecord[1];
            b2 = pKey[1];
            less = b1 < b2;
            if (b1 != b2) {
                cmp = (1 - (int)less) - (int)(less != 0);
                goto check;
            }
            pRecord += 2;
            pKey += 2;
        } while (b1 != 0);
        cmp = 0;
check:
        // Match if strings equal AND (record's id == keyId OR record's id < 0)
        if (cmp == 0) {
            int recordId = *(int *)(record + 0x20);
            if (recordId == keyId || recordId < 0) {
                return (int)index;
            }
        }
        index++;
    } while ((int)index < count);
    return 0xFFFFFFFF;
}