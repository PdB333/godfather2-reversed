// FUNC_NAME: PacketQueue::processMatchingPackets
// Address: 0x007ed300
// This function iterates over a linked list of packet nodes, filters them by type (param_2) and ID (param_3),
// and optionally applies a predicate (param_4). It accumulates sizes and returns the number of processed packets.
// The container (this+0x18) holds a list object with a head sentinel at +0x18.
// Each node has: +0 next, +2 data object, +3 size, +4 data buffer, +5 ID, +7 type, +8 flags.

int __thiscall PacketQueue::processMatchingPackets(int thisPtr, int typeFilter, int* idFilter, int* predicate)
{
    int accumulatedSize = 0;
    int processedCount = 0;
    int containerPtr = 0;

    // Check if already processing (bit 0 of flags at +0x38)
    if ((*(uint32_t*)(thisPtr + 0x38) & 1) == 0) {
        *(uint32_t*)(thisPtr + 0x38) |= 1;  // Set processing flag

        containerPtr = *(int*)(thisPtr + 0x18);  // Get container pointer
        uint32_t* currentNode = *(uint32_t**)(**(int**)(containerPtr + 0x18));  // First node (head sentinel's next)

        while (true) {
            uint32_t* headSentinel = *(uint32_t**)(*(int*)(thisPtr + 0x18) + 0x18);
            // Validate container pointer
            if ((containerPtr == 0) || (containerPtr != *(int*)(thisPtr + 0x18))) {
                assertFail();  // FUN_00b97aea
            }
            if (currentNode == headSentinel) break;  // Reached end of list

            if (containerPtr == 0) {
                assertFail();
            }
            if (currentNode == *(uint32_t**)(containerPtr + 0x18)) {
                assertFail();
            }

            accumulatedSize += currentNode[3];  // Accumulate size from node

            // Filter by type (param_2)
            if (typeFilter == 0) {
                goto processNode;
            } else {
                if (currentNode == *(uint32_t**)(containerPtr + 0x18)) {
                    assertFail();
                }
                if (currentNode[7] == typeFilter) {
                    goto processNode;
                }
                goto skipNode;
            }

processNode:
            // Filter by ID (param_3)
            if (idFilter != 0) {
                if (currentNode == *(uint32_t**)(containerPtr + 0x18)) {
                    assertFail();
                }
                if (*idFilter != currentNode[5]) {
                    goto skipNode;
                }
            }

            // Apply predicate (param_4) if provided
            if ((predicate != 0) &&
                (*(code**)(*predicate + 4))(currentNode + 2, accumulatedSize) == 0) {
                goto skipNode;
            }

            // Process the node
            int originalSize = currentNode[3];
            // Temporary string object on stack (vtable at PTR_FUN_00d6ffac)
            uint32_t* tempVtable = &PTR_FUN_00d6ffac;
            uint32_t tempData = 0;
            uint16_t tempShort = 0;
            short tempShort2 = 0;
            uint32_t tempFlags = 0;

            if ((uint32_t**)(currentNode + 2) != &tempVtable) {
                uint32_t* dataBuffer = (uint32_t*)currentNode[4];
                stringAssign(currentNode + 5);  // FUN_004080d0 - assign from node's data
                int tempSize = currentNode[7];
                uint32_t nodeSize = currentNode[3];
            }
            currentNode[8] |= 1;  // Mark node as processed

            // Advance iterator (returns new container and node)
            int* iteratorResult = (int*)advanceIterator(&tempVtable, containerPtr, currentNode); // FUN_007ecef0
            containerPtr = *iteratorResult;
            currentNode = (uint32_t*)iteratorResult[1];

            // Copy temporary string data
            uint32_t savedData = tempData;
            uint32_t* savedBuffer = dataBuffer;
            char savedFlag = 0;

            if (tempSize == 0) {
                stringClear(&savedData, 0);  // FUN_00408a00
            } else {
                stringSetSize(&savedData, tempSize);  // FUN_00408bf0
            }

            // Validate container again
            headSentinel = *(uint32_t**)(*(int*)(thisPtr + 0x18) + 0x18);
            if ((containerPtr == 0) || (containerPtr != *(int*)(thisPtr + 0x18))) {
                assertFail();
            }
            if (currentNode != headSentinel) {
                if (containerPtr == 0) {
                    assertFail();
                }
                if (currentNode == *(uint32_t**)(containerPtr + 0x18)) {
                    assertFail();
                }
                currentNode[3] += originalSize;  // Add original size to next node (merge?)
            }

            processedCount++;

            // Clean up temporary string
            tempVtable = &PTR_FUN_00d6ffac;
            while (tempShort2 != 0) {
                stringDestructor();  // FUN_00408090
            }
            if ((savedBuffer != 0) && ((tempFlags & 1) == 0)) {
                (*(code**)*savedBuffer)(1);  // Release buffer
            }

            continue;

skipNode:
            if (currentNode == *(uint32_t**)(containerPtr + 0x18)) {
                assertFail();
            }
            currentNode = (uint32_t*)*currentNode;  // Move to next node
        }

        // Clear processing flag
        *(uint32_t*)(thisPtr + 0x38) &= 0xfffffffe;
        processedCount = processedCount;
    }
    return processedCount;
}