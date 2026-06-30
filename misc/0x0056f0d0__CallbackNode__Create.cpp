// FUNC_NAME: CallbackNode::Create
void CallbackNode::Create(void* pOwner, int callbackId) {
    CallbackNode* node = (CallbackNode*)MemoryAllocate(0x14); // sizeof(CallbackNode) = 20
    if (node != nullptr) {
        node->callbackId = callbackId;          // +0x10
        node->pOwner = pOwner;                  // +0x00
        NodeSetupRequest req;                    // 12 bytes on stack: {2, 0x10, 0}
        req.type = 2;                           // local_c
        req.size = 0x10;                        // local_8
        req.unknown = 0;                        // local_4
        
        // Call a virtual function on the owner object with callbackId and request struct
        int result = ((int (__thiscall*)(void*, int, NodeSetupRequest*))(*(void***)pOwner)[0])(pOwner, callbackId, &req);
        node->startResult = result;            // +0x08
        node->endResult = result;              // +0x0C
        node->next = nullptr;                  // +0x04
        gGlobalCallbackNode = node;            // DAT_01205564
    } else {
        gGlobalCallbackNode = nullptr;
    }
}