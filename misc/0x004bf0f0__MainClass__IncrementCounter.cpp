// FUNC_NAME: MainClass::IncrementCounter
void __thiscall MainClass::IncrementCounter(void)
{
    SomeManager* pManager;
    int* piCounter;
    MessageStruct msg;

    pManager = *(SomeManager**)(this + 0x36c);           // +0x36c: pointer to sub-manager
    if (pManager->m_activeCount == 0)                     // +0x064: active count
    {
        InitializeManager(&g_initializationKey);          // FUN_004086d0: init manager with global key
    }
    piCounter = &pManager->m_activeCount;
    (*piCounter)++;                                       // increment counter
    msg.field0 = g_messageID;                             // DAT_01218068: message identifier
    msg.field4 = 0;                                       // reserved
    msg.field8 = 0;                                       // reserved (decompiler shows undefined1, but assume 4 bytes)
    SendMessage(&msg, 0);                                 // FUN_00408a00: dispatch message with zero flags
    return;
}