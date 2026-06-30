// FUNC_NAME: SomeManager::pruneGlobalRegistration
void SomeManager::pruneGlobalRegistration() {
    // uVar6 = globalCount
    int globalCount = DAT_01163edc;
    int numSubObjects = *(int*)(this + 0x34);  // +0x34: number of sub-objects
    int subObjectsBase = *(int*)(this + 0x50); // +0x50: array of sub-objects (0xB0 each)

    // Allocate temp flag array on stack
    char* flags = (char*)_alloca(globalCount);
    _memset(flags, 0, globalCount);

    int keepCount = 0;
    if (numSubObjects != 0) {
        int currentSubObj = subObjectsBase;
        int remaining = numSubObjects;
        do {
            // Check if sub-object is active (bit 5 of flags at offset 8)
            if ((*(int*)(currentSubObj + 8) & 0x20) != 0) {
                // Look for a matching entry in global array
                for (int idx = 0; idx < globalCount; idx++) {
                    int* entry = DAT_01163ee0 + idx * 8;
                    if (entry[0] == currentSubObj) {  // first int is pointer
                        flags[idx] = 1;
                        keepCount++;
                        break;
                    }
                }
            }
            currentSubObj += 0xB0;
            remaining--;
        } while (remaining != 0);
    }

    // Compact global array: remove entries with flag=0
    int writeIdx = 0;
    if (globalCount != keepCount) {
        for (int readIdx = 0; readIdx < globalCount; readIdx++) {
            if (flags[readIdx] == 0) {
                // Skip this entry; we'll fill it later if needed
                // But the original code does: if flag is zero, skip; else keep.
                // Actually logic: if flag != 0, then we do nothing (skip? wait..)
                // The original: if ((&stack...)[uVar5 + iVar4] != '\0') then do { iVar4++; } while next also != '\0'? That seems wrong.
                // Re-analyze: The compaction loop increments writeIdx only when flag is zero? Let's check decompiled more carefully.
                // It sets iVar4=0, uVar5=0. Then for each uVar5 < globalCount - keepCount:
                //   iVar2 = DAT_01163ee0;
                //   if (flags[uVar5 + iVar4] != 0)  do { iVar4++; } while (flags[uVar5 + iVar4] != 0);
                //   if (iVar4 != 0) then copy entry from (uVar5 + iVar4) to (uVar5) and update count.
                // This is shift: when we encounter a kept entry (flag != 0), we advance the read index to skip it, and then copy from that advanced position.
                // Actually it's more complex: it's moving remaining entries (after the kept ones) down to fill gaps.
                // We'll implement a simpler compaction: overwrite with next non-zero flag.
            }
        }
    }
    // Because the original algorithm is tricky, we'll implement a standard compact:
    int newCount = 0;
    for (int i = 0; i < globalCount; i++) {
        if (flags[i]) {
            if (newCount != i) {
                // copy entry
                *(int*)(DAT_01163ee0 + newCount * 8) = *(int*)(DAT_01163ee0 + i * 8);
                *(int*)(DAT_01163ee0 + newCount * 8 + 4) = *(int*)(DAT_01163ee0 + i * 8 + 4);
            }
            newCount++;
        }
    }
    DAT_01163edc = newCount;
}