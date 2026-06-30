// FUNC_NAME: CriticalSection::Leave
undefined4 __thiscall CriticalSection::Leave(CriticalSection *this)
{
    int objectPtr;
    void *critSectionCopy = g_pCriticalSection;   // global critical section data (DAT_0120e94c)
    EnterCriticalSection(&critSectionCopy, 0);    // acquire the lock with 0 timeout
    objectPtr = GetLinkedObject(this);            // retrieve object associated with this lock
    if (objectPtr != 0) {
        // +0x50: flags field, clear bit 8 (0x100) to mark unlocked/released
        *(uint *)(objectPtr + 0x50) &= 0xfffffeff;
    }
    return 1;
}