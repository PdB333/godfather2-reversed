// FUNC_NAME: RenderCommandManager::sortAndOutputSortedList
void __thiscall RenderCommandManager::sortAndOutputSortedList(uint* thisPtr, OutputBuffer* outputBuffer)
{
    // thisPtr offsets:
    // +0x8c: ringBufferSize (max index)
    // +0x90: startIndex
    // +0x94: currentIndex
    // +0x98: ringBuffer (array of RenderEntry, each 0x24 bytes)
    // +0x9c: extraItemList (linked list of ExtraItem nodes)
    // +0xa4: baseOffset (added to computed index)

    int iVar9;
    int iVar8;
    int iVar13;
    int iVar6;
    uint uVar14;
    float fVar3;
    float fVar4;
    RenderEntry* pEntry;
    StackItem* pfStack;
    StackItem* pStackBase;
    StackItem* pStackCur;
    int stackCount; // number of items in temporary stack
    int stackAlloc; // allocated capacity for stack (in triples)

    // Compute initial count for stack based on extra items that have flag bit 11 cleared
    iVar9 = *(int*)(thisPtr + 0x90) - *(int*)(thisPtr + 0x94);
    if (iVar9 < 0) {
        iVar9 = *(int*)(thisPtr + 0x8c) - 1;
    }
    iVar9 = *(int*)(thisPtr + 0xa4) + iVar9;
    iVar8 = iVar9 * -12; // offset for stack alignment (12 = sizeof(StackItem))

    // Count extra items that have flag bit 11 (0x800) cleared
    stackAlloc = 0;
    ExtraItemNode* node = *(ExtraItemNode**)(thisPtr + 0x9c);
    while (node != nullptr) {
        if ((*(ushort*)(node->object + 0x3c) >> 0xb & 1) == 0) {
            stackAlloc = FUN_007168b0(); // returns count? Likely gets a global count or allocates
        }
        node = node->next;
    }
    // NOTE: The above loop seems odd; only last item with cleared flag determines stackAlloc.
    // Possibly the function is mis-decompiled; stackAlloc might be accumulated or FUN_007168b0 returns something else.

    // Allocate temporary stack on stack (via alloca, but we show conceptually)
    // Stack items are triples: [x, y, pointer]
    StackItem* stackBase = (StackItem*)(&stack0xffffffd4 + stackAlloc * 0xc + iVar8); // actual stack address

    // Iterate over ring buffer
    iVar6 = *(int*)(thisPtr + 0x90);
    iVar13 = *(int*)(thisPtr + 0x94);
    stackCount = 0;

    do {
        if (iVar13 == iVar6) {
            // All ring buffer entries processed; now copy sorted stack to output buffer
            if (stackCount > 0) {
                StackItem* src = stackBase;
                do {
                    // outputBuffer->array[outputBuffer->count] = *src
                    if (outputBuffer->count == outputBuffer->capacity) {
                        int newCapacity = (outputBuffer->capacity == 0) ? 1 : (outputBuffer->capacity * 2);
                        FUN_006ad900(); // realloc outputBuffer->array to newCapacity
                    }
                    StackItem* dest = &outputBuffer->array[outputBuffer->count];
                    dest->x = src->x;
                    dest->y = src->y;
                    dest->data = src->data; // pointer stored as float?
                    outputBuffer->count++;
                    src = &src[1]; // advance by 0xc bytes (3 floats)
                    stackCount--;
                } while (stackCount > 0);
            }
            return;
        }

        pEntry = (RenderEntry*)(*(int*)(thisPtr + 0x98) + iVar13 * 0x24);
        if ((*(uint*)(pEntry + 0x10) >> 1 & 1) == 0) { // Check bit 1 (enabled?)
            fVar3 = *(float*)(pEntry + 0x8); // sort key 1 (e.g., x)
            fVar4 = *(float*)(pEntry + 0xc); // sort key 2 (e.g., y)

            // Find insertion position in sorted stack
            uVar14 = 0;
            pfStack = stackBase;
            while (uVar14 < stackCount) {
                // Compare: if (new.y <= current.y && not equal) OR (new.x <= current.x && not equal)
                if ((pfStack->y <= fVar4 && fVar4 != pfStack->y) || (pfStack->x <= fVar3 && fVar3 != pfStack->x)) {
                    // Insert before current: shift elements from uVar14 onward by one
                    if (uVar14 < stackCount) {
                        int numToShift = stackCount - uVar14;
                        StackItem* shiftSrc = &stackBase[stackCount - 1];
                        StackItem* shiftDst = &stackBase[stackCount];
                        do {
                            *shiftDst = *shiftSrc;
                            shiftDst--;
                            shiftSrc--;
                            numToShift--;
                        } while (numToShift > 0);
                    }
                    break; // insert at position uVar14
                }
                uVar14++;
                pfStack++;
            }

            // Insert new element at uVar14
            pfStack = &stackBase[uVar14];
            pfStack->x = fVar3;
            pfStack->y = fVar4;
            pfStack->data = (float)(pEntry + 0x14); // store pointer as float (typecast)
            stackCount++;
        }

        iVar13++;
        if (*(int*)(thisPtr + 0x8c) <= iVar13) {
            iVar13 = 0;
        }
    } while (true);
}