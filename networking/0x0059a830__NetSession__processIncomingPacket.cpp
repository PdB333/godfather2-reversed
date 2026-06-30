// FUNC_NAME: NetSession::processIncomingPacket
// Address: 0x0059a830
// Processes an incoming network packet: validates header, extracts opcode, dispatches to handler via table lookup.

void __fastcall NetSession::processIncomingPacket(int thisPtr)
{
    // thisPtr points to NetSession object
    // +0x08 : pointer to raw packet data (buffer containing header and payload)
    int packetData = *(int *)(thisPtr + 8);
    if (packetData == 0)
        return;

    // Packet header layout (offsets relative to packetData):
    //   +0x02 : unsigned short (packet size)
    //   +0x15 : char (some kind of sequence or type counter)
    // Expectation: packet size == (*(char*)(packetData+0x15) + 0x16)
    unsigned short packetSize = *(unsigned short *)(packetData + 2);
    char expectedSize = *(char *)(packetData + 0x15) + 0x16;
    if ((unsigned int)packetSize != expectedSize)
    {
        // Packet header integrity check failed – assert/abort
        (*(void (**)())(**(int **)0x01205590 + 4))();
    }

    // Build opcode from four bytes at offsets +0x04, +0x08, +0x0c, +0x10.
    // The multiplication by 0x100 (256) composes a 32-bit value in big‑endian style.
    int opcode = ((*(int *)(packetData + 4) * 0x100 +
                   *(int *)(packetData + 8)) * 0x100 +
                  *(int *)(packetData + 0xc)) * 0x100 +
                 *(int *)(packetData + 0x10);

    // Look up handler function for this opcode (returns pointer to a handler object)
    int *handler = (int *)FUN_00599aa0(thisPtr, opcode); // this->getHandler(opcode)
    if (handler == (int *)0x0)
    {
        // No handler registered – error
        (*(void (**)())(**(int **)0x01205590 + 4))();
        return;
    }

    // Call handler's virtual function at vtable index 2 (offset 0x8)
    // Signature: void handler(char arg1, char arg2, char *payload)
    void (*handlerFunc)(char, char, char *) = (void (*)(char, char, char *))(*(int *)(*handler + 8));
    handlerFunc(
        *(char *)(packetData + 0x14),  // first byte argument
        *(char *)(packetData + 0x15),  // second byte argument
        (char *)(packetData + 0x16)    // pointer to remaining payload
    );
}