// FUNC_NAME: CallbackQueueManager::addRequest
void CallbackQueueManager::addRequest(int requestId, int subId, int* keyPtr, void* callbackFunc, void* sourceObj, void* optionalTarget, uint flags, void* unknown, void* userData)
{
    // this+0x04: head of active list
    // this+0x0c: sentinel node (tail marker)
    // this+0x10: free list head
    RequestNode* sentinel = *(RequestNode**)(this + 0x0c);
    RequestNode* node = *(RequestNode**)(this + 0x04);

    // Search for existing entry matching (requestId, subId, keyPtr)
    while (node != sentinel) {
        if (node->requestId == requestId && node->subId == subId && node->keyPtr == keyPtr)
            goto found;
        node = node->next; // node+0x2c (offset 0x2c)
    }

    // Not found: allocate from free list
    node = *(RequestNode**)(this + 0x10);
    if (node == nullptr)
        return;

    // Remove from free list
    *(RequestNode**)(this + 0x10) = node->next; // node+0x2c

    // Insert at tail (before sentinel)
    int prevSentinelPrev = sentinel->prev; // sentinel+0x30
    node->next = sentinel;
    node->prev = sentinel->prev;
    sentinel->prev = node;
    *(int*)(prevSentinelPrev + 0x2c) = (int)node;

    // Initialize node
    node->data = (int)sourceObj;            // node+0x00
    node->eaxObject = (int)this;            // node+0x04 (in_EAX, likely 'this')
    node->requestId = requestId;            // node+0x08
    node->subId = subId;                    // node+0x0c
    node->keyPtr = keyPtr;                  // node+0x10
    node->someFlag = 0;                     // node+0x34 (0xd)
    node->someFlag = (*(uint*)(in_EAX + 0x14) & 2); // in_EAX is the 'this' pointer? Or the 'owner'?
    // Actually the original: piVar2[0xd] = *(uint*)(in_EAX+0x14) & 2; but after setting to 0 earlier.

found:
    RequestNode* foundNode = node; // param_4 = piVar2

    byte sourceFlag = (*(byte*)(sourceObj + 0x44) >> 6) & 1;

    if (flags == 0) {
        if (sourceFlag == 0)
            return;
    } else {
        if (*(float*)(optionalTarget + 0xa0) != SOME_CONSTANT || *(int*)(optionalTarget + 0x84) != 0) {
            // Allocate a secondary node
            void* secondaryNode = FUN_0051f9f0();
            if (secondaryNode != nullptr) {
                FUN_00524b40(secondaryNode, sourceObj, userData);
                int head1 = foundNode->head1; // node+0x28 (offset 0x28)
                int oldNext1 = *(int*)(head1 + 0x44);
                *(int*)(secondaryNode + 0x40) = head1;
                *(int*)(secondaryNode + 0x44) = oldNext1;
                *(int*)(head1 + 0x44) = (int)secondaryNode;
                *(int*)(oldNext1 + 0x40) = (int)secondaryNode;
            }
            goto checkFinal;
        }
    }

checkFinal:
    if (sourceFlag != 0) {
        // Additional callback allocation
        void* callbackNode = FUN_0051f960();
        if (callbackNode != nullptr) {
            *(byte*)(callbackNode + 0x451) = (byte)requestId;
            FUN_005232a0(sourceObj, callbackFunc, optionalTarget, userData);
            int head2 = foundNode->head2; // node+0x1c (offset 0x1c)
            int oldNext2 = *(int*)(head2 + 0x44);
            *(int*)(callbackNode + 0x40) = head2;
            *(int*)(callbackNode + 0x44) = oldNext2;
            *(int*)(head2 + 0x44) = (int)callbackNode;
            *(int*)(oldNext2 + 0x40) = (int)callbackNode;
        }
    }
}