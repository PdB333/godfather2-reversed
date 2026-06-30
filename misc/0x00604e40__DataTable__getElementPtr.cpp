// FUNC_NAME: DataTable::getElementPtr
int __thiscall DataTable::getElementPtr(int thisPtr, int groupIndex, int elementIndex)
{
    // thisPtr+8: pointer to descriptor structure
    // thisPtr+0xc: base address of data array (each element 0x10 bytes)
    int* descriptor = *(int**)(thisPtr + 8);
    // descriptor+8: array of group offsets (each entry 0xc bytes, first 4 bytes used)
    int groupOffset = *(int*)((int)descriptor + 8 + groupIndex * 0xc);
    // groupOffset is the starting index within the data array
    int dataIndex = groupOffset + elementIndex;
    int dataBase = *(int*)(thisPtr + 0xc);
    return dataBase + dataIndex * 0x10;
}