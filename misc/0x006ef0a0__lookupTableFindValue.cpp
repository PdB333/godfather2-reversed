// FUNC_NAME: lookupTableFindValue
int lookupTableFindValue(int* table, int inputParam) {
    // Structure of table (int array):
    // [0] type: 0 = char key, 1 = int key, 2 = float key
    // [1] contextA (first parameter to key generator)
    // [2] contextB (second parameter to key generator)
    // [3] count (number of entries)
    // [4..] entries as pairs: (key, value) for count entries
    // [4 + count*2] default result (when no match)
    int type = table[0];
    int idx = 0; // index into entry list

    if (type == 0) {
        // Compare using char key
        char charKey = FUN_006ebff0(table[1], table[2], inputParam);
        if (table[3] > 0) {
            int* entryPtr = table + 4; // start of first entry key
            do {
                if (*(char*)entryPtr == charKey) break;
                idx++;
                entryPtr += 2;
            } while (idx < table[3]);
        }
        // If found, idx holds the match index; otherwise idx == count
        return table[idx * 2 + 5];
    }
    else if (type == 1) {
        // Compare using int key
        int intKey = FUN_006eb7b0(table[1], table[2], inputParam);
        if (table[3] > 0) {
            int* entryPtr = table + 4;
            while (*entryPtr != intKey) {
                idx++;
                entryPtr += 2;
                if (table[3] <= idx) {
                    return table[idx * 2 + 5]; // default
                }
            }
        }
        return table[idx * 2 + 5]; // matched at idx
    }
    else if (type == 2) {
        // Compare using float key
        float floatKey = (float)FUN_006eb7c0(table[1], table[2], inputParam);
        int count = table[3];

        // Unrolled loop: process 4 entries at a time
        if (count > 3) {
            int* entryPtr = table + 6; // point to second entry key
            do {
                if ((float)entryPtr[-2] == floatKey) goto L_FOUND; // entry [idx]
                if ((float)*entryPtr == floatKey) {
                    return table[idx * 2 + 7]; // entry [idx+1] value
                }
                if ((float)entryPtr[2] == floatKey) {
                    return table[idx * 2 + 9]; // entry [idx+2] value
                }
                if ((float)entryPtr[4] == floatKey) {
                    return table[idx * 2 + 11]; // entry [idx+3] value
                }
                idx += 4;
                entryPtr += 8;
            } while (idx < count - 3);
        }

        // Process remaining entries
        if (idx < count) {
            int* entryPtr = table + idx * 2 + 4;
            while ((float)*entryPtr != floatKey) {
                idx++;
                entryPtr += 2;
                if (count <= idx) {
                    return table[idx * 2 + 5]; // default
                }
            }
        }

L_FOUND:
        return table[idx * 2 + 5];
    }
    else {
        return 0; // invalid type
    }
}