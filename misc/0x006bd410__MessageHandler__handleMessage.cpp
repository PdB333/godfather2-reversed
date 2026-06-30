// FUNC_NAME: MessageHandler::handleMessage
void __thiscall MessageHandler::handleMessage(MessageHandler* this, int* pMessageData)
{
    // Validate message data buffer
    FUN_0046c6a0(pMessageData);

    int messageType = *pMessageData;
    // Compare against known message type IDs
    if (messageType == g_msgTypeEnter) {  // DAT_0120e93c
        FUN_004086d0(&g_msgTypeEnter);
        // Stack-based initialization pattern (likely C++ try/catch or scope guard)
        ScopedStackGuard localGuard; // local_18 and local_8
        localGuard.pGuardTable = &g_guardTable; // PTR_FUN_00e31e2c
        int* pGuardData = nullptr; // local_14
        if (*(this - 0x3c) == nullptr) {
            pGuardData = 0;
        } else {
            pGuardData = (int*)((char*)this + 0xc); // +0x0C next member
        }
        // Initialize guard
        localGuard.guardMagic = g_guardMagic; // DAT_0112a6ac
        localGuard.flag = 0;
        FUN_00408a00(&localGuard, 0); // likely push guard on stack
        // Call virtual function at vtable offset 0x24 from the handler pointer
        (*(code**)(**(int**)((char*)this - 0x3c) + 0x24))();
        // Cleanup if needed
        if (pGuardData != nullptr) {
            FUN_004daf90(&pGuardData);
        }
    } else if (messageType == g_msgTypeLeave) { // DAT_0112fddc
        (*(code**)(**(int**)((char*)this - 0x3c) + 0x2c))();
    } else if (messageType == g_msgTypeAction) { // DAT_0112fdf8
        int actionData = pMessageData[1];
        FUN_006bd3a0(actionData);
        (*(code**)(**(int**)((char*)this - 0x3c) + 0x28))(actionData);
    } else if (messageType == g_msgTypePredicate) { // DAT_01206778
        if (pMessageData[1] != 0) {
            int pObj = *(int*)(pMessageData[1] + 0xc);
            int objId = 0;
            if (pObj != 0) {
                objId = *(int*)(pObj + 0x1c);
            }
            // Compare with stored target ID at this - 0x20
            if (objId == *(int*)((char*)this - 0x20)) {
                // Check flags: flag at this+0x14, global flag at g_globalFlags+0x14 bit0, and g_globalState
                if ((*(char*)((char*)this + 0x14) == 0) && 
                    ((*(BYTE*)(g_globalFlags + 0x14) & 1) == 0) && 
                    (g_globalState == 0)) {
                    FUN_006bd020();
                } else {
                    FUN_006bcfe0();
                }
            }
        }
    }
}