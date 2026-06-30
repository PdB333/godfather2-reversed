// FUNC_NAME: GridData::initFromPool
uint* __thiscall GridData::initFromPool(int thisPtr, uint* bufferHeader)
{
    uint rows, cols;
    uint* poolPtr;
    uint* dataPtr;
    uint elementValue;
    uint* arrayPtr;
    uint* rowPtr;
    uint* colPtr;
    uint localCols;

    // Allocate a memory pool for the grid data (returns pointer to header with two uint32s: rows and element stride?).
    poolPtr = (uint*)allocateMemory();
    *(uint**)(thisPtr + 0x430) = poolPtr;  // +0x430: pool base pointer

    // Data area starts after the two-header words.
    dataPtr = poolPtr + 2;
    *(uint**)(thisPtr + 0x434) = dataPtr;  // +0x434: current data pointer

    // Calculate end pointer from buffer header's size field at +0x18(dec 24)
    // The subtraction of 8 accounts for the two header words.
    *(int*)(thisPtr + 0x438) = *(int*)((int)bufferHeader + 0x18) - 8 + (int)dataPtr;  // +0x438: end of data

    // Total allocated size = rows * 0x24 (36 bytes per row)
    *(uint*)(thisPtr + 0x43c) = *poolPtr * 0x24;  // +0x43c: total size

    // Extract rows and columns from pool header (clamped to max 8 and 32)
    rows = *poolPtr;
    localCols = poolPtr[1];

    if (rows > 7)
        rows = 8;
    *(uint*)(thisPtr + 0x2c) = rows;  // +0x2c: row count (max 8)

    if (localCols > 31)
        localCols = 32;
    *(uint*)(thisPtr + 0x28) = localCols;  // +0x28: column count (max 32)

    // Fill the 2D array at this+0x30 (nested loop: columns then rows)
    if (localCols != 0)
    {
        colPtr = (uint*)(thisPtr + 0x30);  // +0x30: start of grid array
        rowPtr = colPtr;
        do
        {
            for (uint r = rows; r != 0; r--)
            {
                if (dataPtr < *(uint**)(thisPtr + 0x438))
                {
                    // Extract element from data block: each entry is 9 uint32s (36 bytes)
                    elementValue = extractGridElement(dataPtr);  // FUN_004dafd0 - likely reads 36 bytes and returns a compact value
                    *colPtr = elementValue;
                    dataPtr += 9;  // advance by 9 uint32s = 36 bytes
                }
                else
                {
                    *colPtr = 0;
                }
                colPtr++;
            }
            // Move to next column: offset by 8 (since row count is max 8)
            colPtr = rowPtr + 8;
            localCols--;
            rowPtr = colPtr;
        } while (localCols != 0);
    }

    return poolPtr;
}