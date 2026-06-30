// FUNC_NAME: HandleTable::acquireHandle
int __fastcall HandleTable::acquireHandle(uint handleId)
{
    int *handleEntry;
    int refCount;

    handleEntry = *(int **)(DAT_012054ac + (handleId & 0x1fff) * 4);
    if (handleEntry != (int *)0x0) {
        while (handleEntry[3] != handleId) { // +0x0C: handle ID field
            handleEntry = (int *)handleEntry[4]; // +0x10: next entry pointer
            if (handleEntry == (int *)0x0) {
                return -1;
            }
        }
        if (handleEntry != (int *)0x0) {
            LOCK();
            refCount = *handleEntry; // +0x00: reference count
            *handleEntry = refCount + 1;
            UNLOCK();
            return refCount + 1;
        }
    }
    return -1;
}