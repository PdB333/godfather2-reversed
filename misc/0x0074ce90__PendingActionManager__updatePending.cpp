// FUNC_NAME: PendingActionManager::updatePending
undefined4 __thiscall PendingActionManager::updatePending(int this, undefined4 param2) {
    char readyFlag;
    int newPayload;
    int *headPtr;

    // +0x88: mHandle (some object handle, e.g., entity ID or resource handle)
    // +0x8c: mHead (pointer to first node payload in linked list)
    // +0x5c: mParamBuffer (additional parameter for allocation)
    // +0xe4: mFlags (bit 1 selects allocation method)
    // +0xe8: mExtraParam (used in alternative allocation)
    // +0x90: mOldNext (temporary storage for head's next pointer)

    // Condition to add a new node: either forced (param2 != 0), empty list, or handle not valid
    if ((((char)param2 != '\0') || (*(int *)(this + 0x8c) == 0)) ||
        (*(int *)(this + 0x8c) == 0x48) ||
        (readyFlag = validateHandle(*(undefined4 *)(this + 0x88)), readyFlag == '\0')) {
        if ((*(uint *)(this + 0xe4) >> 1 & 1) == 0) {
            newPayload = allocateNodeSimple(*(undefined4 *)(this + 0x88), param2, this + 0x5c);
        } else {
            newPayload = allocateNodeComplex(*(undefined4 *)(this + 0x88), param2, this + 0xe8,
                                            g_globalParamA, this + 0x5c, g_globalParamB);
        }
        headPtr = (int *)(this + 0x8c);
        newPayload = (newPayload == 0) ? 0 : newPayload + 0x48;
        if (*headPtr != newPayload) {
            if (*headPtr != 0) {
                freeNode(headPtr);
            }
            *headPtr = newPayload;
            if (newPayload != 0) {
                // Link new node at head: store old head's next pointer, then set new node's next to old head
                *(undefined4 *)(this + 0x90) = *(undefined4 *)(newPayload + 4);
                *(int **)(newPayload + 4) = headPtr;
            }
        }
    }

    // Always check if the head node is ready to be processed
    headPtr = (int *)(this + 0x8c);
    if ((*headPtr != 0) && (*headPtr != 0x48)) {
        int headerOffset = (*headPtr == 0) ? 0 : *headPtr - 0x48; // -0x48 to get node header
        if (*(char *)(headerOffset + 0xa8) != '\0') { // header +0xa8: mReady flag
            uint relatedPayload = *(int *)(headerOffset + 0x98); // header +0x98: mRelatedHandle or mOwner
            if ((relatedPayload != 0) && (relatedPayload != 0x48)) {
                int relatedHeader = (relatedPayload == 0) ? 0 : relatedPayload - 0x48;
                if (relatedHeader != *(int *)(this + 0x88)) {
                    return 0;
                }
            }
            // Trigger completion callback on handle
            completeCallback(*(undefined4 *)(this + 0x88));
            return 1;
        }
    }
    return 0;
}