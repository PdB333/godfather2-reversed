// FUNC_NAME: PriorityScheduler::processHighestPriorityItem

void PriorityScheduler::processHighestPriorityItem()
{
    // Start at head of node list (+0x04 is head, +0x0C is tail/sentinel)
    int* currentNode = *(int**)(this + 0x04);
    int* bestNode = nullptr;
    int bestItemIndex = 0; // 1 for itemA, 2 for itemB
    float bestPriority = DAT_00e2eff4; // global sentinel: very low priority

    while (currentNode != *(int**)(this + 0x0C))
    {
        float priority;

        // Check item A: pointer at +0x14, end marker at +0x1C
        if (*(int*)(currentNode + 0x14) != *(int*)(currentNode + 0x1C))
        {
            priority = *(float*)(*(int*)(currentNode + 0x14) + 0x14);
        }
        else
        {
            priority = DAT_00e2eff4;
        }

        if (bestPriority < priority)
        {
            bestItemIndex = 1;
            bestNode = currentNode;
            bestPriority = priority;
        }

        // Check item B: pointer at +0x20, end marker at +0x28
        if (*(int*)(currentNode + 0x20) != *(int*)(currentNode + 0x28))
        {
            priority = *(float*)(*(int*)(currentNode + 0x20) + 0x14);
        }
        else
        {
            priority = DAT_00e2eff4;
        }

        if (bestPriority < priority)
        {
            bestItemIndex = 2;
            bestNode = currentNode;
            bestPriority = priority;
        }

        // Move to next node (linked list: +0x2C is next pointer)
        currentNode = *(int**)(currentNode + 0x2C);
    }

    if (bestNode != nullptr)
    {
        if (bestItemIndex == 1)
        {
            int* itemPtr = *(int**)(bestNode + 0x14);
            // Validate item is not the sentinel and not null
            if (itemPtr != *(int**)(bestNode + 0x1C) && itemPtr != nullptr)
            {
                // Remove item from its current list (doubly linked using +0x10 and +0x11)
                *(int**)(itemPtr[0x11] + 0x40) = itemPtr[0x10]; // prev->next = item->next
                *(int**)(itemPtr[0x10] + 0x44) = itemPtr[0x11]; // next->prev = item->prev

                // Call virtual destructor? (vtable+4)
                (**(void (***)(int*) )itemPtr)( itemPtr + 4); // Actually: ((void (*)(int*))(*itemPtr)[1])(itemPtr);

                // Insert item at head of free list (this+0x474 is free list head)
                itemPtr[0x10] = *(int**)(this + 0x474); // item->next = old head
                *(int**)(this + 0x474) = itemPtr;       // head = item
            }
        }
        else // bestItemIndex == 2
        {
            int* someItem = FUN_00520550(); // Ask external function for an item (maybe allocate or dequeue)
            if (someItem != nullptr)
            {
                // Insert item at head of another list (this+0x37C08)
                *(int*)(someItem + 0x40) = *(int*)(this + 0x37C08);
                *(int**)(this + 0x37C08) = someItem;
            }
        }
    }
}