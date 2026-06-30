// FUNC_NAME: ResourceManager::findEntryByKey
int __thiscall ResourceManager::findEntryByKey(int key, char* outName, size_t outNameSize) {
    // this+0x34: pointer to array of Entry structs (each 9 ints, 36 bytes)
    // this+0x38: count of entries
    uint entryCount = *(uint*)(this + 0x38);
    uint i = 0;
    int lastLookup = 0;  // iVar6, tracks last non-null lookup pointer

    if (entryCount == 0) {
        return 0;
    }

    int* entryPtr = *(int**)(this + 0x34);  // base of entry array

    do {
        if (*entryPtr != 0) {  // entry has a non-null pUnknown at +0x00
            // pUnknown is a pointer to some struct; at +0x08 is a pointer to LookupTable
            int* lookupTable = *(int**)(*entryPtr + 8);  // offset +8
            lastLookup = (int)lookupTable;  // save for return on failure

            if (lookupTable != 0) {
                // LookupTable structure: +0x04 = count, +0x08 = pointer to int array
                int count = *(int*)(lookupTable + 1);    // offset +4
                int* table = *(int**)(lookupTable + 2);  // offset +8

                int idx = searchInTable(key, table, count);  // FUN_004cbdc0
                if (idx != -1) {
                    int resultId = table[idx];
                    if (resultId != 0) {
                        // Name is stored at entry offset +4 (char*)
                        char* name = *(char**)(entryPtr + 1);  // entryPtr is int*, +1 adds 4 bytes
                        if (outName != 0 && outNameSize > 0) {
                            if (name != 0 && name[0] != '\0') {
                                strncpy(outName, name, outNameSize);
                                outName[outNameSize - 1] = '\0';
                            } else {
                                outName[0] = '\0';
                            }
                        }
                        return resultId;
                    }
                }
            }
        }
        i++;
        entryPtr += 9;  // advance to next entry (9 ints each)
    } while (i < entryCount);

    return 0;  // not found
}