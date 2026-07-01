// FUNC_NAME: NetSession::sendReliablePacket
bool NetSession::sendReliablePacket(void* thisObj, undefined4 unusedParam, int* packetBuilder)
{
    char status;
    int sequenceNum;
    undefined4* bufferPtr;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 writeBuffer1[4];
    undefined1 writeBuffer2[28];

    bufferPtr = &local_28;
    local_24 = 0;
    sequenceNum = (int)thisObj;
    local_28 = 0;

    // Virtual: start building the packet (vtable+0x1f0)
    (*(void (**)(void))(*packetBuilder + 0x1f0))();

    // Virtual: write 4-byte field (vtable+0xa4) – likely timestamp or ID
    (*(void (**)(void*, void*))(*packetBuilder + 0xa4))(writeBuffer1, &stack0xffffffd4);

    // Virtual: write 28-byte data from thisObj+4 (vtable+0xa4) – probably ghost state
    (*(void (**)(void*, void*))(*packetBuilder + 0xa4))(writeBuffer2, (void*)((int)thisObj + 4));

    // Get sequence number and buffer pointer for final packet
    sequenceNum = FUN_0043b490();                     // getNextSequence?
    bufferPtr = (undefined4*)FUN_0043b490();          // getPacketBuffer?

    // Send the assembled packet with type 0x40122 and flags 0x1ff0000
    status = FUN_0054ebf0(&local_24, &stack0xffffffd0, 0x40122, 0x1ff0000, &sequenceNum, 2, 0, 0, 0);
    return status == '\0';
}