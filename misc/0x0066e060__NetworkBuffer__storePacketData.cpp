// FUNC_NAME: NetworkBuffer::storePacketData
uint __thiscall NetworkBuffer::storePacketData(void *this,
                                                uint16_t param2,
                                                uint16_t param3,
                                                uint16_t param4,
                                                uint16_t param5,
                                                uint32_t param6,
                                                uint32_t param7,
                                                uint32_t param8)
{
    // +0x10: pointer to pool manager
    PoolManager *poolManager = *(PoolManager **)((char *)this + 0x10);
    if (poolManager == nullptr || poolManager->nodeCount > 0x3FF) {
        goto end;
    }

    // +0x18: pointer to current node
    Node *node = poolManager->activeNode;
    if (node == nullptr) {
        goto allocateNewNode;
    }

    // Check if node is full (max 0x40 slots) or ID mismatch
    if (node->slotCount == 0x40 || node->packetId != in_EAX) {
        node = nullptr;
        goto allocateNewNode;
    }

allocateNewNode:
    // +0x08: free node count (max 0x90)
    if (*(uint16_t *)((char *)this + 8) < 0x90) {
        Node *freeNode = *(Node **)((char *)this + 0x14);
        node = nullptr;
        if (freeNode != nullptr) {
            // Pop from free list
            *(Node **)((char *)this + 0x14) = freeNode->next;
            (*(uint16_t *)((char *)this + 8))++;
            node = freeNode;
        }
        // Initialize node
        node->next = nullptr;
        node->packetId = in_EAX;                // +0x04
        node->unk2 = 0;                          // +0x08
        node->slotCount = 0;                     // +0x0C
        // Add to pool manager's node list (tail)
        Node *tail = poolManager->tail;
        if (tail == nullptr) {
            poolManager->head = node;
        } else {
            tail->next = node;
        }
        poolManager->tail = node;
        poolManager->nodeCount++;
    }
    if (node == nullptr) {
        goto end;
    }

    uint32_t slotIndex = node->slotCount;
    node->slotCount = slotIndex + 1;

    // Write slot data (each slot is 16 bytes? Structure inferred from offsets)
    Slot *slot = reinterpret_cast<Slot *>(reinterpret_cast<char *>(node) + 0x10 + slotIndex * 16);
    // Use helper to convert parameters to 16-bit halves (likely float to half)
    ConvertToHalf(*(int *)((char *)this + 0x20), param6, &slot->val1_low, &slot->val1_high);
    ConvertToHalf(*(int *)((char *)this + 0x20), param7, &slot->val2_low, &slot->val2_high);
    ConvertToHalf(*(int *)((char *)this + 0x20), param8, &slot->val3_low, &slot->val3_high);
    slot->data0 = param2;
    slot->data1 = param3;
    slot->data2 = param4;    // corrected based on write order: extraout_EDX[2] = param4, [3] = param5
    slot->data3 = param5;

    poolManager->totalSlots++;
    return 1;
end:
    return 0;
}