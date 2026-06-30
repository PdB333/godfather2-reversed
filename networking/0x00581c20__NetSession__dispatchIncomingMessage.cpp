// FUNC_NAME: NetSession::dispatchIncomingMessage
void __thiscall NetSession::dispatchIncomingMessage(int *this, uint32_t msgType, uint32_t msgData)
{
    // Build a small message header on the stack (17 bytes total)
    // Fields: msgType, msgData, then two zero dwords and one zero byte
    // This likely corresponds to a fixed-format packet header (type, data, sequence, ack?)
    // The zero fields are probably unused or default flags.
    struct {
        uint32_t type;   // +0x00
        uint32_t data;   // +0x04
        uint32_t zero1;  // +0x08 (cleared)
        uint32_t zero2;  // +0x0C (cleared)
        uint8_t  zero3;  // +0x10 (cleared)
    } header;

    header.type  = msgType;
    header.data  = msgData;
    header.zero1 = 0;
    header.zero2 = 0;
    header.zero3 = 0;

    // Call virtual function at vtable offset 0x14 (5th virtual function)
    // This handler receives a pointer to the constructed header and processes it.
    // In TNL/NetSession, this is likely "handlePacket" or "processIncoming".
    void (*processFn)(void*) = (void (*)(void*))(*(int*)this + 0x14);
    processFn(&header);
}