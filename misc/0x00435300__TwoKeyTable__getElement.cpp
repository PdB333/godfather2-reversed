// FUNC_NAME: TwoKeyTable::getElement
struct TwoKeyTable
{
    int *m_pBucketList; // +0x10: pointer to array of bucket pointers? Actually used as base for array of ints.
    int m_nBucketCount; // +0x14: number of buckets or existence flag? Checked as non-zero.
    // ... other members?
};

struct Bucket
{
    ushort m_usWidth;     // +0x0A: number of columns? First dimension size.
    ushort m_usHeight;    // +0x0C: number of rows? Second dimension size.
    int *m_pIndexData;    // +0x10: pointer to 2-byte index grid (ushort) of size m_usWidth * m_usHeight.
    int *m_pElementArray; // +0x14: pointer to 0x20-byte element structs referenced by indices.
    void *m_pRowMap;      // +0x18: array used to map input param_2 to row index (size? maybe m_usWidth entries of 8 bytes each).
    void *m_pColMap;      // +0x1C: array used to map input param_3 to column index (size? maybe m_usHeight entries of 8 bytes each).
};

// Return value: pointer to element if found, else &DAT_0120a5ec (sentinel).
void * __thiscall TwoKeyTable::getElement(int thisPtr, unsigned int rowKey, unsigned int colKey, int bucketIndex)
{
    Bucket *pBucket;
    int *piVar;
    ushort uRowIdx, uColIdx;
    int iVar, iVar2;
    int iRowMapIdx, iColMapIdx;
    ushort usIndex;

    // Check if bucket list exists
    if (*(int *)(thisPtr + 0x14) == 0)
        return &DAT_0120a5ec;

    // Determine bucket
    if (bucketIndex == 0)
    {
        // Use default first bucket
        iVar = *(int *)(*(int *)(thisPtr + 0x10) + 4);
    }
    else
    {
        iVar = getBucket(&bucketIndex); // 0x435840: returns index into bucket array
        if (iVar < 0)
            return &DAT_0120a5ec;
        piVar = (int *)(*(int *)(thisPtr + 0x10) + 4 + iVar * 8);
        if (piVar == (int *)0x0)
            return &DAT_0120a5ec;
        iVar = *piVar;
    }

    if (iVar == 0)
        return &DAT_0120a5ec;

    pBucket = (Bucket *)iVar;

    // Map row key to row index
    uRowIdx = pBucket->m_usWidth; // original width used as limit for mapping
    iRowMapIdx = findRowIndex(rowKey, uRowIdx); // 0x4354c0: maps rowKey to an index in the row map array
    if (iRowMapIdx >= 0)
        uRowIdx = *(ushort *)((int)pBucket->m_pRowMap + 4 + iRowMapIdx * 8); // get mapped row index from the row map array

    // Map col key to col index
    uColIdx = pBucket->m_usHeight;
    iColMapIdx = findColIndex(colKey, uColIdx); // 0x435500: maps colKey to an index in the col map array
    if (iColMapIdx >= 0)
        uColIdx = *(ushort *)((int)pBucket->m_pColMap + 4 + iColMapIdx * 8); // get mapped col index

    // Validate indices
    if (uRowIdx < pBucket->m_usWidth && uColIdx < pBucket->m_usHeight)
    {
        // Compute linear index into the index grid
        usIndex = *(ushort *)((int)pBucket->m_pIndexData + (pBucket->m_usHeight * uRowIdx + uColIdx) * 2);
        if (usIndex != 0xFFFF)
            return (void *)(usIndex * 0x20 + (int)pBucket->m_pElementArray);
    }

    return &DAT_0120a5ec;
}