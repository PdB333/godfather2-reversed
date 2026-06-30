// FUNC_NAME: ObjectFlagManager::findOrAllocateFlagEntry
int __thiscall ObjectFlagManager::findOrAllocateFlagEntry(int param_2)
{
    uint* puVar1;
    int iVar2;
    int iVar3;
    int* piVar4;

    iVar3 = *(int *)(this + 0xb4) + -1; // m_entryCount - 1 (last index)
    if (-1 < iVar3) {
        iVar2 = *(int *)(this + 0xb0); // m_entryArray pointer
        piVar4 = (int *)(iVar2 + iVar3 * 8); // point to entry at index iVar3
        do {
            if (*piVar4 == param_2) { // entry->id matches?
                if (-1 < iVar3) {
                    puVar1 = (uint *)(iVar2 + 4 + iVar3 * 8); // &entry.flags
                    *puVar1 = *puVar1 | 4; // set bit 2 (0x4) on flags
                    return iVar2 + 4 + iVar3 * 8; // return pointer to flags
                }
                break;
            }
            iVar3 = iVar3 + -1;
            piVar4 = piVar4 + -2; // move to previous entry (8 bytes back)
        } while (-1 < iVar3);
    }
    // Not found – allocate a new entry with the ID and flag mask 4
    iVar3 = FUN_004478c0(param_2, 4); // allocateEntry(param_2, 4)
    return iVar3;
}