// FUNC_NAME: TNLConnection::processCompletedPackets
void TNLConnection::processCompletedPackets()
{
    PacketNode *currentNode = *(PacketNode **)(this + 0x54); // +0x54: head of pending operation list
    bool bAnyFreed = false;

    if (currentNode == nullptr)
        return;

    while (true)
    {
        PacketNode *nextNode = currentNode->next; // +0x00: next pointer

        // Only process nodes of type 6 (e.g., PacketType::Free)
        if (currentNode->type == 6) // +0x2c (offset 0xB0)
        {
            // Remove currentNode from the linked list
            if (currentNode->prev == nullptr) // +0x04
            {
                *(PacketNode **)(this + 0x54) = currentNode->next; // update head
                if (currentNode->next != nullptr)
                    currentNode->next->prev = nullptr;
            }
            else
            {
                currentNode->prev->next = currentNode->next;
                if (currentNode->next != nullptr)
                    currentNode->next->prev = currentNode->prev;
            }

            // Update tail pointer (this + 0x58)
            PacketNode **tailPtr = (PacketNode **)(this + 0x58);
            *tailPtr = currentNode->prev;
            if (*tailPtr != nullptr)
                (*tailPtr)->next = nullptr;

            // Clear prev and next
            currentNode->prev = nullptr;
            currentNode->next = nullptr;

            // Process ring buffer of reference-counted objects
            while (true)
            {
                int *refCountPtr = currentNode->refCountPtr; // +0x33 (offset 0xCC)
                if (refCountPtr == nullptr)
                {
                    // Lock ring buffer critical section
                    EnterCriticalSection(&currentNode->ringBufferCS); // +0x3a
                    if (currentNode->ringBufferCount > 0) // +0x39
                    {
                        currentNode->refCountPtr = currentNode->ringBuffer[currentNode->ringBufferIndex]; // +0x36 base, +0x38 index
                        currentNode->ringBufferIndex = (currentNode->ringBufferIndex + 1) % currentNode->ringBufferSize; // +0x37 size
                        currentNode->ringBufferCount--;
                    }
                    LeaveCriticalSection(&currentNode->ringBufferCS);

                    if (currentNode->refCountPtr == nullptr)
                        break;
                }

                // Decrement reference count
                (*currentNode->refCountPtr)--;
                if (*currentNode->refCountPtr == 0)
                {
                    // Add the freed object to the circular buffer (free list)
                    EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x28)); // +0x28: free list CS
                    int freeIndex = *(int *)(this + 0x24); // +0x24: current count in buffer
                    int maxFree = *(int *)(this + 0x1c);  // +0x1c: buffer size
                    if (freeIndex < maxFree)
                    {
                        int insertPos = *(int *)(this + 0x20) + freeIndex; // +0x20: base offset
                        if (insertPos >= maxFree)
                            insertPos -= maxFree;
                        *(int **)(*(int *)(this + 0x18) + insertPos * 4) = currentNode->refCountPtr; // +0x18: buffer array
                        *(int *)(this + 0x24) = freeIndex + 1;
                    }
                    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x28));
                    bAnyFreed = true;
                }
                currentNode->refCountPtr = nullptr; // +0x33 cleared
            }

            // If there's a pending delete object, call its destructor via vtable
            if (currentNode->pendingDelete != nullptr) // +0x42
            {
                (**(void (__thiscall **)(void *))(**(int **)(this + 0x94) + 8))(currentNode->pendingDelete); // vtable offset 8
                currentNode->pendingDelete = nullptr;
            }

            // Process the list of pending sends (currentNode + 0x44)
            PacketNode *sendNode = currentNode->pendingSends; // +0x44
            while (sendNode != nullptr)
            {
                uint *refCount = (uint *)sendNode->next; // +0x04??? Actually careful: the code uses puVar5 = (uint *)piVar9[1]; piVar9[1] is offset 4? Let's re-evaluate:
                // From decompiled:
                // puVar5 = (uint *)piVar9[1];  // piVar9 is sendNode, so puVar5 = sendNode->next? But then later *puVar5 gets decremented. So sendNode->next is a ref count? That seems weird.
                // Actually the list is a singly linked list where each node's 'next' pointer holds the ref count? Let's re-examine decompiled part:
                // piVar9 = (int *)piVar10[0x44];  // piVar9 = pendingSends list head
                // do {
                //   puVar5 = (uint *)piVar9[1];   // piVar9[1] = offset 4 in the node
                //   piVar6 = (int *)*piVar9;       // piVar9[0] = next pointer
                //   if (puVar5 != (uint *)0x0) {
                //     if (*puVar5 < 2) { ... } else { *puVar5 = *puVar5 - 1; }
                //     piVar9[1] = 0;
                //   }
                //   // Move piVar9 to free list
                //   piVar9[0] = *(int *)(in_EAX + 0x10);  // set next to this->freeHead
                //   ...
                //   piVar9 = piVar6;   // advance to next node
                // } while (piVar6 != 0);
                // So in the pending send list, each node has:
                //   - offset 0: next pointer (node*)
                //   - offset 4: pointer to a ref count (uint*)
                // The ref count is decremented; if it drops below 2, it's freed via vtable. Otherwise just decremented.
                // After processing, the node is moved to the free list (this+0x10/0x14).
                // Given this, let's model pending sends with a small struct.
                // We'll implement accordingly.

                // For reconstruction we'll keep the logic as close as possible.
                uint *refCount = (uint *)sendNode->field4; // offset 4 in send node
                PacketNode *nextSend = (PacketNode *)sendNode->next; // offset 0

                if (refCount != nullptr)
                {
                    if (*refCount < 2)
                    {
                        // Free via vtable
                        (**(void (__thiscall **)(void *))(**(int **)(this + 0x94) + 8))(refCount);
                    }
                    else
                    {
                        (*refCount)--;
                    }
                    sendNode->field4 = 0;
                }

                // Add sendNode to the free list (this + 0x10 is head, +0x14 is tail)
                sendNode->next = *(PacketNode **)(this + 0x10);
                if (*(PacketNode **)(this + 0x10) == nullptr)
                    *(PacketNode **)(this + 0x14) = sendNode;
                *(PacketNode **)(this + 0x10) = sendNode;

                sendNode = nextSend;
            }

            // Clear pending sends list
            currentNode->pendingSends = nullptr; // +0x44
            currentNode->pendingSendCount = 0;    // +0x45

            // Reset various fields
            *(byte *)(currentNode + 2) = 0; // +0x08? Actually offset 8? No: piVar10 + 2 -> offset 8 (since int* increment by 4). So byte at offset 8.
            currentNode->field2a = 0;      // +0x2a
            currentNode->field2b = -1;     // +0x2b
            currentNode->type = -0x67;     // +0x2c -> set to -103 (maybe sentinel)
            currentNode->field2d = 0;      // +0x2d
            currentNode->field2f = 0;      // +0x2f
            currentNode->field30 = 0;      // +0x30
            currentNode->field31 = 0;      // +0x31
            currentNode->field43 = 0;      // +0x43
            currentNode->field34 = 0;      // +0x34

            // Reinsert currentNode into the free list (this + 0x5c head, +0x60 tail)
            currentNode->next = *(PacketNode **)(this + 0x5c);
            currentNode->prev = nullptr;
            if (*(PacketNode **)(this + 0x5c) == nullptr)
                *(PacketNode **)(this + 0x60) = currentNode;
            else
                (*(PacketNode **)(this + 0x5c))->prev = currentNode;
            *(PacketNode **)(this + 0x5c) = currentNode;
        }

        // Move to next node
        currentNode = nextNode;
        if (currentNode == nullptr)
        {
            if (!bAnyFreed)
                return;
            // If any node was freed and a condition is met, call another function
            if (*(int *)(this + 0x48) != 0 && *(int *)(*(int *)(this + 0x48) + 0xb0) == 2)
            {
                processPendingActions(); // FUN_004d1ab0
            }
            return;
        }
    }
}