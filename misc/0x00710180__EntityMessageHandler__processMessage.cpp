// FUNC_NAME: EntityMessageHandler::processMessage
bool __thiscall EntityMessageHandler::processMessage(void* message) {
    // +0x60: m_pendingAction (pointer to some object)
    // +0x64: m_activeAction (pointer to some object)
    // +0x68: m_flags1 (maybe pointer)
    // +0x6c: m_flags2
    int* pendingAction = *(int**)(this + 0x60);
    int* activeAction = *(int**)(this + 0x64);
    int* flags1 = *(int**)(this + 0x68);
    int* flags2 = *(int**)(this + 0x6c);

    // Check if the object is idle (all four fields null)
    if (pendingAction == 0 && activeAction == 0 && flags1 == 0 && flags2 == 0) {
        // Idle state: try to process the incoming message
        if (message != 0) {
            // +4 offset in message structure holds a pointer to an embedded object
            int* embeddedObj = *(int**)((char*)message + 4);
            if (embeddedObj != 0) {
                // The embedded object is at offset +0x48 from its containing object
                int* containerObj = (int*)((char*)embeddedObj - 0x48);
                if (containerObj != (int*)0x0) {
                    void* outParam = 0;
                    // Call virtual method at vtable+0x10 with event hash
                    bool result = (**(code**)(*containerObj + 0x10))(0x369ac561, &outParam);
                    if (result) {
                        return result; // Actually returns the result from the virtual call
                    }
                }
            }
        }
        return false;
    } else {
        // Non-idle state: try to obtain an object from the pending action field
        int* obj = (int*)FUN_00446100(this + 0x60, 0); // External helper - likely gets a container from the pending action
        if (obj != (int*)0x0) {
            void* outParam = 0;
            bool result = (**(code**)(*obj + 0x10))(0x369ac561, &outParam);
            if (result) {
                return result;
            }
            return false;
        }
        return false;
    }
}