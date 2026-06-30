// FUNC_NAME: MessageRouter::routeMessage
// Function at 0x006be4b0: Message routing/dispatcher.
// Processes a message pointed to by pMessageData and routes it based on message type.
// this: pointer to MessageRouter instance (offsets: +0x14 = m_pTargetObjectID, +0x1c = m_expectedTypeId)
// pMessageData: pointer to a structure { int messageType; void* extraData; }

void __thiscall MessageRouter::routeMessage(int this, int* pMessageData)
{
    int messageType;
    int* extraData;
    int objectPtr;

    messageType = *pMessageData;               // first field = message type ID
    extraData = (int*)pMessageData[1];          // second field = pointer to extra data block

    if (messageType == *(int*)(this + 0x1c))   // matches this->m_expectedTypeId ?
    {
        if (*(int*)(this + 0x14) != 0)          // this->m_pTargetObjectID != 0
        {
            objectPtr = getObjectById(*(int*)(this + 0x14));  // lookup object from ID
            if (objectPtr != 0)
            {
                invokeMethod(*(undefined4*)(objectPtr + 0x40)); // call function at +0x40
                return;
            }
        }
    }
    else
    {
        if (messageType == g_globalScriptTaskId)  // DAT_0120e93c
        {
            if (*(int*)(this + 0x14) != 0)
            {
                objectPtr = getObjectById(*(int*)(this + 0x14));
                if (objectPtr != 0)
                {
                    invokeMethod(*(undefined4*)(objectPtr + 0x40));
                }
            }
            releaseGlobalScriptTask();            // FUN_004086d0 on g_globalScriptTaskId
            return;
        }
        if (messageType == g_globalInputEventId)  // DAT_0112a620
        {
            // extraData layout assumed: [4 bytes type, 4 bytes data?];
            // Here extraData[0] might be a pointer to another structure.
            if (*(int*)(extraData[0] + 4) + 0x38) == *(int*)(this + 0x14))
            {
                invokeMethod(*(undefined4*)(extraData[0] + 0xc));
            }
        }
    }
    return;
}