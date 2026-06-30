// FUNC_NAME: PoolManager::allocateFromBestFit

void PoolManager::allocateFromBestFit(void)
{
    int *currentNode;
    int *bestNode;
    int bestSlot;
    int *removedElement;
    float bestValue;
    float currentValue;

    // Start from the head of the node list (this+0x04)
    currentNode = *(int **)(this + 0x04);
    bestNode = nullptr;
    bestSlot = 0;
    bestValue = -FLT_MAX; // DAT_00e2eff4 is likely -FLT_MAX

    // Traverse the linked list of nodes (each node has left and right sublists)
    while (currentNode != *(int **)(this + 0x0c)) // until tail
    {
        // Check left sublist (offset +0x14 = head, +0x1c = tail)
        currentValue = -FLT_MAX;
        if (*(int *)(currentNode + 0x14) != *(int *)(currentNode + 0x1c))
        {
            // Get the metric from the first element in the left sublist (offset +0x14 of element)
            currentValue = *(float *)(*(int *)(currentNode + 0x14) + 0x14);
        }
        if (bestValue < currentValue)
        {
            bestSlot = 1;
            bestNode = currentNode;
            bestValue = currentValue;
        }

        // Check right sublist (offset +0x20 = head, +0x28 = tail)
        currentValue = -FLT_MAX;
        if (*(int *)(currentNode + 0x20) != *(int *)(currentNode + 0x28))
        {
            currentValue = *(float *)(*(int *)(currentNode + 0x20) + 0x14);
        }
        if (bestValue < currentValue)
        {
            bestSlot = 2;
            bestNode = currentNode;
            bestValue = currentValue;
        }

        // Move to next node in the list (offset +0x2c)
        currentNode = *(int **)(currentNode + 0x2c);
    }

    if (bestNode != nullptr)
    {
        if (bestSlot == 1)
        {
            // Remove the first element from the left sublist
            removedElement = *(int **)(bestNode + 0x14);
            if ((removedElement != *(int **)(bestNode + 0x1c)) && (removedElement != nullptr))
            {
                // Unlink from the sublist (offsets +0x40 = prev, +0x44 = next)
                *(int *)(removedElement[0x11] + 0x40) = removedElement[0x10]; // next->prev = prev
                *(int *)(removedElement[0x10] + 0x44) = removedElement[0x11]; // prev->next = next

                // Call virtual destructor or cleanup (vtable+4)
                (**(code **)(*removedElement + 4))();

                // Push onto the free list at this+0x474
                removedElement[0x10] = *(int *)(this + 0x474); // prev = current head
                *(int **)(this + 0x474) = removedElement;     // head = removedElement
            }
        }
        else // bestSlot == 2
        {
            // Allocate a new element via FUN_00520550 (likely a factory or allocator)
            int *newElement = FUN_00520550();
            if (newElement != nullptr)
            {
                // Push onto the free list at this+0x37c08
                newElement[0x10] = *(int *)(this + 0x37c08); // prev = current head
                *(int *)(this + 0x37c08) = (int)newElement;  // head = newElement
            }
        }
    }
}