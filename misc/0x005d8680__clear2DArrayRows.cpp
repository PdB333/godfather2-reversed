// FUNC_NAME: clear2DArrayRows
void __thiscall clear2DArrayRows(int this, int rowStartOffset, int startRow, size_t rowSize, int numRows)
{
    // this+0x04: stride (size of one row in bytes, including any padding)
    // this+0x0C: base pointer to the start of the 2D array data
    int stride = *(int *)(this + 4);
    void *base = *(void **)(this + 0xC);
    void *rowPtr = (void *)((int)base + rowStartOffset + stride * startRow);
    
    if (numRows > 0) {
        do {
            memset(rowPtr, 0, rowSize);
            rowPtr = (void *)((int)rowPtr + stride);
            numRows--;
        } while (numRows != 0);
    }
}