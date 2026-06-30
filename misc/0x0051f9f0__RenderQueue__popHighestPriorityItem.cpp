// FUNC_NAME: RenderQueue::popHighestPriorityItem
int* __fastcall RenderQueue::popHighestPriorityItem(void* thisPtr)
{
    // Offset 0x37c08: cachedCurrentItem pointer (maybe to speed up consecutive pops)
    int** cachedItemPtr = *(int***)((char*)thisPtr + 0x37c08);

    // Check if cache is valid and both flags at +0x43080 and +0x43088 are not 0x90 (e.g., inactive/disabled)
    if (cachedItemPtr != nullptr 
        && *(int*)((char*)thisPtr + 0x43080) != 0x90 
        && *(short*)((char*)thisPtr + 0x43088) != 0x90)
    {
        // Advance the cache to the next item in the linked list
        *(int**)((char*)thisPtr + 0x37c08) = (int*)cachedItemPtr[0x10];
        return (int*)cachedItemPtr;  // Return the cached item
    }

    // Otherwise, traverse the global list of nodes (each node holds a sub-list of items)
    int nodeIter = *(int*)((char*)thisPtr + 4);           // +0x04: head of node list
    int bestNode = 0;
    int headNode = *(int*)((char*)thisPtr + 0xc);         // +0x0c: sentinel/tail of node list

    // Initialize best priority with a sentinel value (DAT_00e2eff4, likely -FLT_MAX)
    float bestPriority = *(float*)0x00e2eff4;

    if (nodeIter != headNode)
    {
        do
        {
            float nodePriority = *(float*)0x00e2eff4;  // Reset for each node, but not actually used as default?
            int* subList = *(int**)(nodeIter + 0x20);   // +0x20: head of sub-list for this node
            int* subListEnd = *(int**)(nodeIter + 0x28); // +0x28: tail/sentinel of sub-list

            if (subList != subListEnd)
            {
                // The priority is stored at offset 0x14 of the first sub-item
                nodePriority = *(float*)(subList + 0x14);
                // Note: In the original code, the float is read from *(*(int*)(nodeIter+0x20)+0x14)
            }

            if (bestPriority < nodePriority)
            {
                bestNode = nodeIter;
                bestPriority = nodePriority;
            }

            nodeIter = *(int*)(nodeIter + 0x2c);  // +0x2c: next node in the global list
        } while (nodeIter != headNode);
    }

    // If a best node was found, extract the first item from its sub-list
    if (bestNode != 0)
    {
        int** bestSubList = *(int***)(bestNode + 0x20);
        int* item = (int*)bestSubList;  // item is the first element in the sub-list

        if (item != *(int**)(bestNode + 0x28)) // Check item exists
        {
            // Unlink item from the doubly-linked sub-list
            // +0x11*4 = offset 0x44 for prev pointer? Actually offset 0x40 and 0x44 are next/prev
            // Since int size 4: index 0x10 is offset 0x40, index 0x11 is offset 0x44
            int* itemPrev = (int*)item[0x11]; // previous item (at +0x44)
            int* itemNext = (int*)item[0x10]; // next item (at +0x40)
            *(int**)((char*)itemPrev + 0x40) = itemNext; // set prev->next
            *(int**)((char*)itemNext + 0x44) = itemPrev; // set next->prev

            // Cleanup flag at +0x34*4 = offset 0xD0? No, 0x34 * 4 = 0xD0.
            if (item[0x34] != 0)
            {
                // Call cleanup function (e.g., free temporary resources)
                FUN_0066dfe0();
                item[0x34] = 0;  // Clear flag
            }

            // Call virtual function at index 1 (vtable+4) to process the item (e.g., render)
            void (*processFunc)(int*) = *(void (**)(int*))(item[0]); // vtable
            processFunc(item);  // Actually (**(code**)(*piVar1+4))() means vtable[1] (since +4 bytes from vtable base)
            // In C++: item->vtable->method1();

            return item;
        }
    }

    return nullptr;
}