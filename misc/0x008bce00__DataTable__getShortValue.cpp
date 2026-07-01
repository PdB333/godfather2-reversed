//FUNC_NAME: DataTable::getShortValue
// Function address: 0x008bce00
// Role: Retrieves a short value from a 2D lookup table indexed by an ID and a column offset.
// The table is stored as a pointer at this+0x8. Each row has 0x16 (22) shorts (44 bytes).
// Returns 0 if the ID is not found (lookup returns -1).

short __thiscall DataTable::getShortValue(int thisPtr, int id, int columnIndex)
{
    int rowIndex = lookupIndexById(id); // FUN_008bcb50: returns row index or -1
    if (rowIndex >= 0)
    {
        // Access table: pointer at this+0x8, row stride = 0x16 shorts, column = columnIndex
        short* table = *(short**)(thisPtr + 8);
        return table[rowIndex * 0x16 + columnIndex];
    }
    return 0;
}