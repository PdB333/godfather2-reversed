// FUN_004e0e80: PoolManager::addPoolBlock
void PoolManager::addPoolBlock()
{
    // Allocate a 0x3004-byte block from the system allocator
    int* pBlock = reinterpret_cast<int*>(FUN_009c8e50(0x3004)); // external allocator
    if (pBlock == nullptr)
        return;

    // Zero out the element area: each element is 12 bytes, first 8 bytes cleared
    int* pCur = pBlock + 1; // skip header (first 4 bytes)
    int count = 0x3ff;      // 1023 elements
    do {
        pCur[0] = 0;
        pCur[1] = 0;
        pCur += 3;          // advance 12 bytes to next element
        count--;
    } while (count >= 0);

    // Build the linked list: each element's next pointer (at offset +12) points to the next element (16 bytes ahead)
    count = 0x3ff;
    pCur = pBlock;          // start at base
    do {
        pCur[3] = reinterpret_cast<int>(pCur + 4); // (int*)pCur + 4 = next element base
        count--;
        pCur += 3;          // stride of 12 bytes
    } while (count != 0);

    // Terminate the last element's next pointer
    pBlock[0xc00] = 0;      // offset 0x3000 from block start

    // Insert the entire block into the pool's free list (singly linked)
    // this+0x10 : head pointer to free blocks
    // this+0x08 : pointer to first free element (or tail)
    pBlock[0] = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x10);
    *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x10) = pBlock;
    *reinterpret_cast<int**>(reinterpret_cast<char*>(this) + 0x08) = pBlock + 1;
}