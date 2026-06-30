// FUNC_NAME: SomeGlobalArrayAccessor::getByIndex
int FUN_0067bf20(int index)
{
    // Accesses a global table starting at DAT_01129808 (likely an array of 4-byte entries)
    // Returns the value at offset (index * 4) from that base address
    return *(int *)(DAT_01129808 + index * 4);
}