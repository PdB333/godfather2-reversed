// FUNC_NAME: ActionPacketBuilder::insertActionNode

int ActionPacketBuilder::insertActionNode(int param_1)
{
    // this->m_bufferControl is at offset 0x10, contains buffer capacity and used size
    BufferControl* bufferCtrl = *(BufferControl**)((int)this + 0x10);
    if (bufferCtrl->m_usedSize >= bufferCtrl->m_capacity) {
        // Buffer overflow - handle error
        FUN_00627360();
    }

    // Allocate a new action node (type 8)
    ActionNode* newNode = (ActionNode*)FUN_00638a40(8);
    int* writePtr = *(int**)((int)this + 8);
    *writePtr = 7;                 // packet type 7 (action node)
    *(writePtr + 1) = (int)newNode; // packet payload: pointer to new node
    *(int*)((int)this + 8) = (int)writePtr + 8; // advance write pointer

    // Initialize the action node's linked list fields (offsets 0x10 and 0x14)
    newNode->m_next = nullptr;
    newNode->m_prev = nullptr;

    // param_1 is a pointer to an action list or a parent node (offset 0x48 signifies insertion point)
    if (param_1 != 0) {
        param_1 = param_1 + 0x48; // walk to the insertion point
    } else {
        param_1 = 0;
    }

    // Insert newNode into a doubly-linked list at param_1
    if (newNode->m_next != (ActionNode*)param_1) {
        if (newNode->m_next != nullptr) {
            FUN_004daf90(&newNode->m_next); // unlink existing?
        }
        newNode->m_next = (ActionNode*)param_1;
        if (param_1 != 0) {
            newNode->m_prev = *(ActionNode**)(param_1 + 4);
            *(ActionNode**)(param_1 + 4) = newNode; // update previous node's prev to newNode
        }
    }

    // Check some condition (possibly error flag)
    if (FUN_00627c90() != 0) {
        FUN_004aeb70(&PTR_DAT_00e326dc);
    }

    // Now handle patching of previous packets in the buffer
    int currentWritePos = *(int*)((int)this + 8);
    int packetStart = currentWritePos - 8; // start of the packet just written

    // Check the type of the packet 16 bytes before current write position (previous packet)
    if (*(int*)(currentWritePos - 0x10) == 5) {
        // Packet type 5: data packet - patch its payload (offset 8) to point to newNode's m_prev?
        // Actually it writes the value from (newNode + 4) to (previous packet payload + 8)
        *(int*)(*(int*)(currentWritePos - 0xc) + 8) = *(int*)((int)newNode + 4);
    } else if (*(int*)(currentWritePos - 0x10) == 7) {
        // Packet type 7: another action node - patch similarly and then remove the current packet
        *(int*)(*(int*)(currentWritePos - 0xc) + 8) = *(int*)((int)newNode + 4);
        // Remove the just-written packet by restoring write pointer
        *(int*)((int)this + 8) = currentWritePos - 8;
        return 1;
    }

    // For type 5, also remove the current packet (undo the write) and return
    *(int*)((int)this + 8) = currentWritePos - 8;
    return 1;

    // Error path (if allocation failed)
    FUN_00627bd0("Failed to create %s object.\n", &DAT_00e326c8);
    code* errorHandler = (code*)__swi(3); // breakpoint / assertion
    return (*errorHandler)();
}