// FUNC_NAME: NameTable::findNameByHash
char* NameTable::findNameByHash(NameTable* this, int nameHash) {
    uint numEntries;
    int iVar2;
    int nameTablePtr;
    uint uVar4;
    char* entry;

    int param_2_copy = nameHash;
    uVar4 = 0;
    int local_4 = 0;
    nameTablePtr = FUN_005f0560(this, &param_2_copy, &local_4); // resolve table or context
    
    if (((local_4 != 0) && (nameTablePtr != 0)) && (nameTablePtr = *(int*)(local_4 + 0xc), nameTablePtr != 0)) {
        // +0x0C: data segment pointer
        if (*(int*)(nameTablePtr + 0x40) == 0) {
            return "<no nametables found>";
        }
        // +0x40: name table base offset (relative to segment)
        // +0x38: count of entries
        numEntries = *(uint*)(nameTablePtr + 0x38);
        entry = (char*)(*(int*)(nameTablePtr + 0x40) + nameTablePtr);
        if (numEntries != 0) {
            do {
                iVar2 = FUN_004dafd0(entry); // likely hash calculation function
                if (iVar2 == param_2_copy) {
                    return entry;
                }
                uVar4 = uVar4 + 1;
                entry = entry + 0x30; // each entry is 0x30 bytes
            } while (uVar4 < numEntries);
        }
        return "<name not found>";
    }
    return "<name not found>";
}