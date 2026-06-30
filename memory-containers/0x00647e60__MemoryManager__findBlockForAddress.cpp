// FUNC_NAME: MemoryManager::findBlockForAddress
uint __fastcall MemoryManager::findBlockForAddress(void *thisPtr, uint address)
{
    uint block = *(uint *)((uint)thisPtr + 0x460); // current block pointer, starts at head of free list?
    uint sentinel = (uint)thisPtr + 0x448; // end marker (maybe pointer to tail node)

    while (true)
    {
        if (block == sentinel)
            return 0; // address not found in any block

        // Check if address lies within this block: block base <= address < block base + block size
        if ((block <= address) && (address < *(int *)(block + 4) + block))
            break;

        block = *(uint *)(block + 0x18); // next block in linked list
    }
    return block; // returns pointer to the block descriptor containing the address
}