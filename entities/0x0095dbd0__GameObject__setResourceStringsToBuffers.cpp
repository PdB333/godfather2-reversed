// FUNC_NAME: GameObject::setResourceStringsToBuffers
void __thiscall GameObject::setResourceStringsToBuffers(int param_2, int param_3, int param_4)
{
    char *pResString;        // +0x00 local variable for retrieved strings
    int unkFlag;             // +0x04 always 0, passed to copy function
    void (*pFreeFunc)(char*); // +0x08 never initialized, likely a bug in decompilation

    pResString = (char *)0x0;
    unkFlag = 0;
    pFreeFunc = (void (*)(char*))0x0;

    // Retrieve first string resource using ID stored at this+0x14 (e.g., display name ID)
    FUN_00604000(*(int *)(this + 0x14), &pResString, 1);
    if (pResString == (char *)0x0) {
        pResString = (char *)0x0120546e; // fallback to empty string constant
    }
    FUN_005c4660(param_2, pResString, param_4, unkFlag); // copy to param_2 buffer

    // Retrieve second string resource using ID stored at this+0x38 (e.g., description ID)
    FUN_00603d30(*(int *)(this + 0x38), &pResString, 1);
    if (pResString == (char *)0x0) {
        pResString = (char *)0x0120546e; // fallback to empty string constant
    }
    FUN_005c4660(param_3, pResString, param_4, unkFlag);

    // Decompilation artifact: pFreeFunc is always null, so this is a no-op.
    if (pResString != (char *)0x0) {
        (*pFreeFunc)(pResString);
    }
}