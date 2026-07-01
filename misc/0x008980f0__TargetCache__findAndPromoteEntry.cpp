// FUNC_NAME: TargetCache::findAndPromoteEntry
// Address: 0x008980f0
// This function searches a small cache of 4 entries (each 0x18 bytes) for a matching target.
// If found, it promotes the entry to the front of a 3-entry array (MRU list) and clears the "next" pointers.
// The search can be by key (4 ints at targetData+0x20) or by pointer (if flag bit 1 at targetData+0x1f54 is set).

struct TargetCacheEntry {
    int field0;      // +0x00
    int field4;      // +0x04
    int field8;      // +0x08
    int fieldC;      // +0x0C
    int field10;     // +0x10
    int field14;     // +0x14
};

class TargetCache {
public:
    // +0x00: first 4 ints of entry0 (key)
    // +0x10: start of 4-entry search table (each 0x18 bytes, but only first 16 bytes used for key)
    // +0x20: 3-entry MRU array (each 0x18 bytes)
    // +0x48..0x58: next pointers (cleared on promotion)

    void findAndPromoteEntry(int targetData);
};

void __thiscall TargetCache::findAndPromoteEntry(int targetData) {
    int iVar4;
    int* piVar2;
    uint uVar3;
    int* puVar5;
    bool bVar6;

    iVar4 = 0;
    uVar3 = 0;
    piVar2 = (int*)(this + 0x10); // start of search table

    do {
        if ((*(uint*)(targetData + 0x1f54) >> 1 & 1) == 0) {
            // Compare by key (4 ints)
            if (piVar2[-4] == *(int*)(targetData + 0x20) &&
                piVar2[-3] == *(int*)(targetData + 0x24) &&
                piVar2[-2] == *(int*)(targetData + 0x28)) {
                bVar6 = (piVar2[-1] == *(int*)(targetData + 0x2c));
                goto LAB_00898146;
            }
        } else {
            // Compare by pointer (handle)
            if (*piVar2 == 0) {
                bVar6 = (targetData == 0);
            } else {
                bVar6 = (*piVar2 - 0x48 == targetData);
            }
LAB_00898146:
            if (bVar6) {
                // Found match at index uVar3
                if (uVar3 < 3) {
                    // Shift entries in MRU array (at this+0x20) to make room
                    puVar5 = (int*)(this + 0x20 + uVar3 * 0x18);
                    iVar4 = 3 - uVar3;
                    do {
                        // Copy entry from current position to previous slot
                        puVar5[-8] = puVar5[-2];
                        puVar5[-7] = puVar5[-1];
                        puVar5[-6] = *puVar5;
                        puVar5[-5] = puVar5[1];
                        // Handle pointer field (field at offset +0x10 relative to entry)
                        if (puVar5 + -4 != puVar5 + 2) {
                            iVar1 = puVar5[2];
                            piVar2 = puVar5 + -4;
                            if (puVar5[-4] != iVar1) {
                                if (puVar5[-4] != 0) {
                                    FUN_004daf90(piVar2); // likely reference counting or pointer assignment
                                }
                                *piVar2 = iVar1;
                                if (iVar1 != 0) {
                                    puVar5[-3] = *(int*)(iVar1 + 4);
                                    *(int**)(iVar1 + 4) = piVar2;
                                }
                            }
                        }
                        puVar5 += 6;
                        iVar4--;
                    } while (iVar4 != 0);
                }
                // Clear next pointers (offsets 0x48..0x58)
                if (*(int*)(this + 0x58) != iVar4) {
                    FUN_004daf90((int*)(this + 0x58));
                    *(int*)(this + 0x58) = iVar4;
                }
                *(int*)(this + 0x54) = iVar4;
                *(int*)(this + 0x50) = iVar4;
                *(int*)(this + 0x4C) = iVar4;
                *(int*)(this + 0x48) = iVar4;
                return;
            }
        }
        uVar3++;
        piVar2 += 6; // advance to next search entry (0x18 bytes)
        if (uVar3 > 3) {
            return;
        }
    } while (true);
}