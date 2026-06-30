// FUNC_NAME: TNLConnection::advanceSendSequence
// Address: 0x006b4da0
// Role: Increments the send sequence counter and triggers actions if thresholds crossed.
// Object layout (at param_1):
//   +0x40: packetTypeId (int, e.g. a hash like 0x637b907)
//   +0x58: windowSize (uint, max sequence number before blocking?)
//   +0x64: sendCompleteLimit (uint, when to fire a callback)
//   +0x68: currentSequence (uint, incremented)
//   +0x6c: sendBufferLimit (uint, if exceeded triggers flush)
//   +0x78: flushBufferFuncPtr (void*? callable)

void __fastcall TNLConnection::advanceSendSequence(TNLConnection* this)
{
    uint currentSeq;
    undefined **local_14;
    int objPtr;
    undefined4 formatString;
    undefined ***local_8;
    undefined1 padding;

    // Only advance if we haven't hit the window limit
    currentSeq = this->currentSequence;
    if (currentSeq < this->windowSize)
    {
        this->currentSequence = currentSeq + 1;
        if (this->sendBufferLimit < this->currentSequence)
        {
            // Notify system to flush send buffer (first param = packetTypeId, second = 1)
            FUN_008c7890(this->packetTypeId, 1);
        }
        if (this->flushBufferFuncPtr != (void*)0)
        {
            // Call the optional flush callback
            FUN_006b4b50();
        }

        // Setup debug logging variables (likely for a trace message)
        local_8 = &local_14;
        local_14 = &PTR_LAB_00d5dbb0;   // Debug format string
        formatString = DAT_0112a5a4;     // Possibly additional string
        padding = 0;
        objPtr = (int)this;
        // Log the event with 0 as extra param
        FUN_00408a00(&formatString, 0);

        // Special case: if packet type is "ghost update" (0x637b907) and sequence count equals the complete limit,
        // fire a specific callback (event id 0x59e83a3b)
        if ((this->packetTypeId == 0x637b907) && 
            (this->currentSequence == this->sendCompleteLimit))
        {
            FUN_00894c90(0x59e83a3b);
        }
    }
}