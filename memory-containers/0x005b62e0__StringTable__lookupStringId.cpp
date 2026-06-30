// FUNC_NAME: StringTable::lookupStringId
// Address: 0x005b62e0
// Role: Looks up a string in a name-to-ID table, returns the associated integer ID, or 0 if not found.

unsigned int StringTable::lookupStringId(const char *name)
{
    int iVar1;
    int iVar2;
    int iVar3;

    // Get singleton string manager
    iVar1 = StringManager::getInstance();
    // Navigate to the table: +8 -> pointer to another structure, +4 -> pointer to StringTable
    iVar1 = *(int *)(*(int *)(iVar1 + 8) + 4);
    iVar3 = 0;
    // +0x30 = number of entries
    if (0 < *(int *)(iVar1 + 0x30)) {
        do {
            // Each entry is 8 bytes: +0 = string pointer, +4 = index into values array
            iVar2 = __stricmp(*(const char **)(*(int *)(iVar1 + 0x34) + iVar3 * 8), name);
            if (iVar2 == 0) {
                // +0x18 = base of uint32 array; index from entry+4 gives element
                return *(unsigned int *)(*(int *)(iVar1 + 0x18) + 
                                         *(int *)(*(int *)(iVar1 + 0x34) + 4 + iVar3 * 8) * 4);
            }
            iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(iVar1 + 0x30));
    }
    return 0;
}