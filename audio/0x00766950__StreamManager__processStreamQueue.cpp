// FUNC_NAME: StreamManager::processStreamQueue
void __fastcall StreamManager::processStreamQueue(StreamManager* this)
{
    int iVar1;
    StreamNode dummyHead1; // local_20
    StreamNode* oldNext1;  // local_1c
    StreamNode dummyHead2; // local_18
    StreamNode* oldNext2;  // local_14
    int unused1;           // local_10
    int unused2;           // local_c
    int* globalPointer;    // local_8
    int command;           // local_4

    // Initialize internal state (likely clears temporary flags)
    prepareInternalState();

    // Capture global singleton pointer (DAT_00d5d740)
    globalPointer = g_StreamManager;

    // Check if there is an active stream node in the queue (offset +0x54)
    if ((this->m_pCurrentStreamNode != 0) && (this->m_pCurrentStreamNode != (StreamNode*)0x48)) {
        iVar1 = (int)this->m_pCurrentStreamNode;

        // Build a dummy head for the linked list of stream nodes
        dummyHead1.next = 0;
        dummyHead1.prev = 0;
        dummyHead2.next = 0;
        dummyHead2.prev = 0;
        if ((iVar1 != 0) && ((iVar1 != 0x48 && (iVar1 != 0)))) {
            oldNext1 = (StreamNode*)(iVar1 + 4); // actually &(node->next)
            *(int**)(iVar1 + 4) = &dummyHead1.next; // detach and point to dummy
            dummyHead1.next = (StreamNode*)iVar1;
        }

        // Similarly for the pending stream node (offset +0x50)
        if (this->m_pPendingStreamNode == 0) {
            iVar1 = 0;
        }
        else {
            iVar1 = (int)this->m_pPendingStreamNode + 0x48;
        }
        if ((iVar1 != 0) && (dummyHead2.next = 0, dummyHead2.prev = 0, dummyHead2.next = (StreamNode*)iVar1, iVar1 != 0)) {
            oldNext2 = (StreamNode*)(iVar1 + 4);
            *(int**)(iVar1 + 4) = &dummyHead2.next;
        }

        // Set command/priority flags
        unused2 = 0;
        unused1 = 0;
        command = 0xa5; // likely kStreamPriorityNormal or similar

        // Lazily allocate a StreamInstance object if needed
        if (this->m_pStreamInstance == 0) {
            iVar1 = operator_new(0x98);
            if (iVar1 == 0) {
                this->m_pStreamInstance = 0;
            }
            else {
                this->m_pStreamInstance = StreamInstance::Construct();
            }
        }

        if (this->m_pStreamInstance != 0) {
            // Enqueue the dummy list of current stream nodes
            QueuePushList(&dummyHead1);

            // Compute the sound index from the stream node (offset -0x48)
            if (this->m_pCurrentStreamNode == 0) {
                iVar1 = 0;
            }
            else {
                iVar1 = (int)this->m_pCurrentStreamNode - 0x48; // get base of node
            }
            // Play the sound effect associated with this stream
            PlaySoundEffect(g_soundIdTable[iVar1], this->m_pStreamInstance, 0, 1, 0);
        }

        // Clean up the temporary dummy lists
        if (dummyHead2.next != 0) {
            ReleaseNodeList(&dummyHead2);
        }
        if (dummyHead1.next != 0) {
            ReleaseNodeList(&dummyHead1);
        }
    }
}