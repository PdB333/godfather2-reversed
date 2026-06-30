// FUNC_NAME: TNLConnection::processDeferredEvents
void TNLConnection::processDeferredEvents(TNLConnection* this) {
    int* pPacketData;
    uint32_t flags = 0;
    int* pCurrentData;
    uint32_t eventType;
    PacketNode* pNode;
    
    // Save previous packet state
    *(int*)((int)this + 0x8) = *(int*)((int)this + 0x4);
    
    // Check if current packet type is special (0x11f = 287)
    if (*(int*)((int)this + 0x14) == 0x11f) {
        // Convert special packet type to actual event
        eventType = FUN_00639c70((int)this + 0x10);
        *(int*)((int)this + 0xC) = eventType;
    } else {
        // Normal case: shift packet chain
        *(int*)((int)this + 0xC) = *(int*)((int)this + 0x14);
        *(int*)((int)this + 0x10) = *(int*)((int)this + 0x18);
        *(int*)((int)this + 0x14) = 0x11f;
    }
    
    // Iterate through packet node list
    pPacketData = *(int**)(*(int*)((int)this + 0x1C) + 0x14);
    for (pNode = (PacketNode*)pPacketData; pNode != NULL; pNode = (PacketNode*)pNode->next) {
        if (pNode->someFlag != 0) {
            break; // Found active node
        }
        flags |= pNode->dataField;
    }
    
    // If no active node found, print debug message
    if (flags == 0) {
        FUN_00638b80("no loop to break");
    }
    
    // Process active node if flags were accumulated
    if (flags != 0) {
        // Send event with combined data: high byte from node info + 0x21
        FUN_006438e0((pNode->someCounter << 0x18) | 0x21,
                     *(int*)(*(int*)((int)this + 0xC) + 8));
    }
    
    // Reset pending state
    *(int*)((int)this + 0x20) = 0xFFFFFFFF;
    
    // Send disconnect completion event
    FUN_006438e0(0x7FFF94, 
                 *(int*)(*(int*)((int)this + 0xC) + 8));
    
    // Release object twice (reference counting)
    FUN_00642880((int)this);
    FUN_00642880((int)this);
}