// FUNC_NAME: FreeList::coalesceInsertBlock
// Inserts a free block into a sorted doubly-linked free list, coalescing with adjacent free blocks if possible.
// Structure: Free block header: +0x00: size (bytes), +0x04: next, +0x08: prev
// List header: +0x10: head pointer
void* FreeList::coalesceInsertBlock(void* thisPtr, void* blockToInsert)
{
    // 'thisPtr' points to a structure containing the free list head at offset 0x10
    int* listHead = (int*)thisPtr;
    int* insertBlock = (int*)blockToInsert;
    
    int* current = (int*)listHead[4]; // +0x10 -> head pointer
    int* prevBlock = nullptr;
    
    // Traverse sorted list (by address ascending) to find insertion point
    if (current != nullptr)
    {
        do
        {
            int* node = current;
            current = node;
            if (insertBlock < node) // Address comparison
                break;
            current = (int*)node[1]; // next pointer at +0x04
            prevBlock = node;
        } while (current != nullptr);
    }
    
    if (prevBlock != nullptr)
    {
        int prevSize = prevBlock[0]; // size of previous block
        // Check if insertBlock is immediately after prevBlock (coalesce with previous)
        if ((int*)((char*)prevBlock + prevSize) == insertBlock)
        {
            // Check if coalesce also with next block
            if ((current == nullptr) || ((int*)((char*)insertBlock + insertBlock[0]) != current))
            {
                // Only merge with previous
                prevBlock[0] = prevSize + insertBlock[0]; // add sizes
            }
            else
            {
                // Merge both previous and next into prevBlock
                prevBlock[0] = prevSize + insertBlock[0] + current[0]; // sum all three sizes
                prevBlock[1] = current[1]; // next becomes next of current
                if (current[1] != 0) // if there is a node after current, update its prev
                {
                    int** nextNext = (int**)(current[1] + 8); // prev pointer at +0x08 of the node after current
                    *nextNext = prevBlock;
                }
                return prevBlock; // return the coalesced block (prevBlock)
            }
            return prevBlock;
        }
        // No coalesce with previous; insert after prevBlock
        prevBlock[1] = (int)insertBlock;
        goto finish_insert;
    }
    else
    {
        // List empty, insertBlock becomes head
        listHead[4] = (int)insertBlock; // head pointer at +0x10
    }
    
finish_insert:
    // Attempt to coalesce with next block
    if ((current == nullptr) || ((int*)((char*)insertBlock + insertBlock[0]) != current))
    {
        // Not adjacent to next block, just set links
        insertBlock[2] = (int)prevBlock; // prev pointer at +0x08
        insertBlock[1] = (int)current;   // next pointer at +0x04
    }
    else
    {
        // Coalesce with next block
        insertBlock[0] = insertBlock[0] + current[0]; // merge sizes
        insertBlock[2] = current[2]; // inherit prev from next (now merged)
        insertBlock[1] = current[1]; // inherit next from next
        // Update 'current' for the next pointer update below (current is now the node after the merged area)
        current = (int*)current[1];
    }
    
    if (current != nullptr)
    {
        current[2] = (int)insertBlock; // update prev of the node after insertBlock
    }
    
    return insertBlock;
}