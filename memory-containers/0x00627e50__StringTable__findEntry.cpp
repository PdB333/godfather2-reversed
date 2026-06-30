// FUNC_NAME: StringTable::findEntry
// Address: 0x00627e50
// Role: Looks up a null-terminated string (key) in a string table, returning a result from a matched entry.
// The table is traversed backward from a cursor pointer at this+0x08.
// Each entry is 8 bytes: 4-byte type, 4-byte pointer to data (containing string at offset +0x10 for type==4).
// If a match is found, calls helper FUN_00625b60 and returns its value; otherwise returns 0.

int __thiscall StringTable::findEntry(byte *key) {
    byte bCur;
    int iResult;
    byte *pbData;
    bool bLess;
    uint uIndex1, uIndex2;

    // Check if the table is initialized (FUN_00625f80 probably checks valid state)
    if (!FUN_00625f80()) {
        return 0;
    }

    // Possibly acquire or sync something (FUN_00625e70)
    FUN_00625e70();

    // Current entry pointer at this+0x08
    int *pEntry = *(int **)(this + 8);
    if (pEntry - 8 != nullptr) {   // if pEntry is not at the start (entry has a header)
        int iType = *(int *)(pEntry - 8); // entry type at offset -8 from pEntry
        if (iType == 4) {
            // For type 4, the string is at ( *(pEntry-4) + 0x10 )
            pbData = (byte *)(*(int *)(pEntry - 4) + 0x10);
        } else {
            // Check if this type is also valid (FUN_00633990 returns truthy)
            if (!FUN_00633990()) {
                pbData = nullptr;
            } else {
                pbData = (byte *)(*(int *)(pEntry - 4) + 0x10);
            }
            // Compare indices: if the container at this+0x10 has current index (0x20) <= max index (0x24), 
            // trigger some overflow/limit handler (FUN_00627360)
            uIndex1 = *(uint *)(*(int *)(this + 0x10) + 0x20);
            uIndex2 = *(uint *)(*(int *)(this + 0x10) + 0x24);
            if (uIndex1 <= uIndex2) {
                FUN_00627360();
            }
        }

        if (pbData != nullptr) {
            // Compare key with the entry's string byte-by-byte (null-terminated)
            do {
                bCur = *pbData;
                bLess = bCur < *key;
                if (bCur != *key) {
                    // strcmp-style: return -1 if pbData < key, +1 if pbData > key
                    iResult = (1 - (int)bLess) - (int)(bLess != 0);
                    goto done;
                }
                if (bCur == 0) break;
                bCur = pbData[1];
                bLess = bCur < key[1];
                if (bCur != key[1]) {
                    // Actually, the same logic applies for subsequent pairs? The code jumps to LAB_00627ee0 for any mismatch.
                    // But after the first byte, it only checks if they are equal; if not, it goes to the same label.
                    // So the label at 0x627ee0 is reused. In C++, we can just break and compute at the end.
                    // But to replicate exactly: we compute iResult as above and goto done.
                    iResult = (1 - (int)bLess) - (int)(bLess != 0);
                    goto done;
                }
                pbData += 2;
                key += 2;
            } while (bCur != 0);
            // If all bytes matched, iResult = 0
            iResult = 0;
done:
            if (iResult == 0) {
                // Match found: move cursor back one entry (decrement by 8) and call helper
                *(int *)(this + 8) -= 8;
                return FUN_00625b60();
            }
        }
    }

    // No match: still decrement cursor and return 0
    *(int *)(this + 8) -= 8;
    return 0;
}