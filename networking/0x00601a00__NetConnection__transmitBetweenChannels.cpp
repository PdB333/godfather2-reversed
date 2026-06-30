// FUNC_NAME: NetConnection::transmitBetweenChannels
// Address: 0x00601a00
// Role: Transfers data from one channel to another within the network connection's channel array.
// The channel array is at offset +0x70, each entry 12 bytes (0xc): struct { int id; int unused; int dataPtr; }
int __thiscall NetConnection::transmitBetweenChannels(int srcChannelIndex, int dstChannelIndex)
{
    int* srcEntry = (int*)(this + 0x70 + *srcChannelIndex * 0xc); // +0x70: channel array base
    int srcId = *srcEntry;
    if (srcId == 0)
        return 0;
    int srcDataPtr = srcEntry[2]; // +8: data pointer
    if (srcDataPtr == 0)
        return 0;

    int* dstEntry = (int*)(this + 0x70 + *dstChannelIndex * 0xc);
    int dstId = *dstEntry;
    if (dstId == 0)
        return 0;
    int dstDataPtr = dstEntry[2]; // +8: data pointer
    if (dstDataPtr == 0 || dstId == srcId)
        return 0;

    // Initiate transfer from source channel's data to destination channel
    sendDataToChannel(dstId, dstDataPtr);                 // FUN_005f5c20
    int result = buildPacketFromData(srcDataPtr, local_c); // FUN_005f5f20 (local_c is 12-byte buffer)
    flushSendQueue();                                     // FUN_005f5bb0
    return result;
}