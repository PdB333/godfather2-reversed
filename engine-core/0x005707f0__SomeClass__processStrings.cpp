// FUNC_NAME: SomeClass::processStrings
void __thiscall SomeClass::processStrings(void)
{
    char cVar1;
    char *pcVar2;
    int iVar3;
    // +0x34: m_pResource (pointer to some resource)
    // +0x24: m_count (number of items)
    // +0x28: m_items (array of pointers to strings)

    if (*(int *)(this + 0x34) != 0) {
        FUN_00587680(); // likely releaseResource()
    }

    iVar3 = 0;
    if (0 < *(int *)(this + 0x24)) {
        do {
            // Each item is a pointer to a null-terminated string
            pcVar2 = (char *)**(undefined4 **)(*(int *)(this + 0x28) + iVar3 * 4);
            if (pcVar2 != (char *)0x0) {
                // Advance to end of string (possibly a strlen-like loop)
                cVar1 = *pcVar2;
                while (cVar1 != '\0') {
                    pcVar2 = pcVar2 + 1;
                    cVar1 = *pcVar2;
                }
            }
            FUN_005737c0(); // likely processString(pcVar2) but pcVar2 now points to '\0'
            iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(this + 0x24));
    }
    return;
}