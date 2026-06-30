//FUNC_NAME: Array2D::clearRows
// Address: 0x005d8680
// Clears a rectangular region of a 2D array by zeroing out a specified number of rows,
// starting from a given row and column offset. The array stride and base pointer are stored
// in the object at offsets +0x4 and +0xC respectively.

void __thiscall Array2D::clearRows(int this, int colOffset, int rowStart, size_t elementSize, int rowCount)
{
    // Compute pointer to the first element to clear:
    // base = *(int*)(this + 0xC)   // base address of the 2D array
    // stride = *(int*)(this + 0x4) // bytes per row
    // _Dst = base + stride * rowStart + colOffset
    void *dst = (void *)(*(int *)(this + 4) * rowStart + *(int *)(this + 0xC) + colOffset);

    // Clear each row
    if (rowCount > 0) {
        do {
            _memset(dst, 0, elementSize);
            dst = (void *)((int)dst + *(int *)(this + 4)); // advance by stride
            rowCount--;
        } while (rowCount != 0);
    }
}