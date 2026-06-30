// FUNC_NAME: NetworkManager::registerMessages
void NetworkManager::registerMessages(void)
{
    // this is in unaff_ESI
    if (this != (NetworkManager *)0x0) {
        // Register message type 0x11 with CRC 0x8c036aab
        void *msgData1 = getMessageString(0); // FUN_0049a640
        this->addMessage(0x11, msgData1); // vtable+4
        registerMessageCRC(0x8c036aab, this, 0x11); // FUN_00497960

        // Register message type 0x13 with CRC 0x46e7afe1
        void *msgData2 = getMessageString(0);
        this->addMessage(0x13, msgData2);
        registerMessageCRC(0x46e7afe1, this, 0x13);

        // Register message type 0x10 with CRC 0x1a271621
        void *msgData3 = getMessageString(0);
        this->addMessage(0x10, msgData3);
        registerMessageCRC(0x1a271621, this, 0x10);

        // Register message type 0x12 with CRC 0xd7d6fc22
        void *msgData4 = getMessageString(0);
        this->addMessage(0x12, msgData4);
        registerMessageCRC(0xd7d6fc22, this, 0x12);
    }

    // Register two notify callbacks (vtable+0x18 = registerNotify)
    int vtable = *(int *)this;
    uint32_t notifyId0 = getNotifyId0(); // FUN_0049a850
    (*(void (__thiscall *)(NetworkManager *, int, uint32_t))(vtable + 0x18))(this, 0, notifyId0);

    vtable = *(int *)this;
    uint32_t notifyId1 = getNotifyId1(); // FUN_0049a860
    (*(void (__thiscall *)(NetworkManager *, int, uint32_t))(vtable + 0x18))(this, 1, notifyId1);
}