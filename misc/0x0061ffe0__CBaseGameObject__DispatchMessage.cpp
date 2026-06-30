// FUNC_NAME: CBaseGameObject::DispatchMessage
// Function address: 0x0061ffe0
// Calls a virtual method at vtable+4 with message type and three arguments.
// Message structure: { uint32 type, uint32 padding, void* arg1, void* arg2, void* arg3 }
// FUN_00620210 is a pre-call hook (likely logging/initialization).

typedef void (__thiscall *MessageHandler)(void* self, uint32 type, void* arg1, void* arg2, void* arg3);

struct Message {
    uint32 type;    // +0x00
    uint32 pad;     // +0x04 (skipped)
    void* arg1;     // +0x08
    void* arg2;     // +0x0C
    void* arg3;     // +0x10
};

int CBaseGameObject::DispatchMessage(CBaseGameObject* thisObj, Message* msg) {
    // Pre-call hook
    if (thisObj != nullptr) {
        FUN_00620210(); // Possibly logs or sets state
    }

    // Get vtable and call the second virtual method (offset 4)
    // vtable is stored at *thisObj (first member)
    void** vtable = *(void***)thisObj;
    MessageHandler handler = (MessageHandler)(*(void**)(vtable + 1)); // offset 4 = second pointer
    handler(thisObj, msg->type, msg->arg1, msg->arg2, msg->arg3);

    return 1; // success
}