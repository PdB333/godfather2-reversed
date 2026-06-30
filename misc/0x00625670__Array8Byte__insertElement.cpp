// FUNC_NAME: Array8Byte::insertElement
// Address: 0x00625670
// Role: Inserts a new element into the dynamic array at specified index by shifting existing elements to the right.
//       The new element's data is taken from the first element (duplicate). The function allocates storage via FUN_00625430 when inserting at the front.

void __thiscall Array8Byte::insertElement(int index)
{
    uint32* pDest;   // puVar1 - address where the new element will be placed
    uint32* pSrc;    // puVar2 - current element being shifted

    // If inserting at the very beginning (index <= 0), allocate a new temporary storage
    if (index < 1) {
        pDest = (uint32*)FUN_00625430();   // allocate space for one element
    } else {
        // Compute destination pointer relative to end:
        // endPtr + (index - 1) * 8   (since each element is 8 bytes)
        // This assumes endPtr points one past the last element.
        pDest = (uint32*)(*(int*)(this + 0x0C) - 8 + index * 8);
    }

    // Shift elements to the right between the current last element and the insertion point
    // Start from the last element (pointer at +0x08 is the start of data? actually it's the end? The loop moves backwards)
    // The loop copies each element (2 uint32s) one position to the right.
    for (pSrc = *(uint32**)(this + 0x08); pDest < pSrc; pSrc -= 2) {
        pSrc[0] = pSrc[-2];   // copy first uint32
        pSrc[1] = pSrc[-1];   // copy second uint32
    }

    // At this point, pSrc points to the original first element.
    // Copy the first element into the destination (makes room for intended insertion)
    pSrc = *(uint32**)(this + 0x08);
    pDest[0] = pSrc[0];
    pDest[1] = pSrc[1];

    // Note: The caller is expected to overwrite the duplicate first element with actual new data.
    return;
}