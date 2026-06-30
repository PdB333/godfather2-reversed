// FUNC_NAME: DataTable::getEntry
undefined4 __thiscall DataTable::getEntry(uint key, byte *outStatus, int *outHandle)
{
    int lookupResult[2] = {0};
    int *entryPtr = (int *)lookupByKey(lookupResult);
    if (outHandle && entryPtr && (subEntryPtr = (int *)(entryPtr[3]) != 0))
    {
        byte statusByte = *(byte *)(subEntryPtr + 1); // +4 in byte units
        *outHandle = (int)entryPtr;
        *outStatus = statusByte;
        int index = *(int *)(lookupResult[0] + 1); // +4
        return *(undefined4 *)((int)subEntryPtr + 0x58 + index * 4);
    }
    return 0;
}