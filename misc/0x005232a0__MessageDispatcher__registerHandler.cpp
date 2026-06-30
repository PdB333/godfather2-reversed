// FUNC_NAME: MessageDispatcher::registerHandler
void MessageDispatcher::registerHandler(int handlerId, int /*unused*/, void* handlerNode, bool setFlagBit) {
    // +0x460: ushort flags (bit0 indicates something)
    this->flags = 0;
    if (setFlagBit) {
        this->flags |= 1;
    }

    // +0x454: store the handler ID
    this->handlerId = handlerId;

    // +0x458: pointer to the head of an intrusive linked list of handler nodes
    // The node is embedded in the handlerNode structure at offset +4.
    // The node structure at handlerNode+4 has:
    //   - at offset 0 (handlerNode+4): data? (unused here)
    //   - at offset 4 (handlerNode+8): backlink pointer (int*)
    int* headPtr = this->head;
    int* newNode = handlerNode ? (int*)((char*)handlerNode + 4) : nullptr;

    if (headPtr != newNode) {
        if (headPtr) {
            // Free the previous list head? (likely deallocates the old node chain)
            FUN_004daf90(headPtr);
        }
        this->head = newNode;

        if (newNode) {
            // +0x45c: saved old backlink from the new node
            this->savedBacklink = *(newNode + 1); // newNode[1] == handlerNode+8
            // Set the node's backlink to point to the head pointer field of this object
            *(newNode + 1) = &this->head;
        }
    }

    // +0x462, +0x450: additional flags
    this->field_0x462 = 0;
    this->field_0x450 = false;  // byte

    // +0x464: some sub-object initialization
    FUN_005205b0(&this->field_0x464);

    // +0x451: another flag; if not set, process the handlerNode further
    if (!this->field_0x451) {
        FUN_005247a0(handlerNode);
    }
}