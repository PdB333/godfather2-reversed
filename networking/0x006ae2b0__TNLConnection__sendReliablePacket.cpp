// FUNC_NAME: TNLConnection::sendReliablePacket
void __thiscall TNLConnection::sendReliablePacket(TNLConnection* thisPtr)
{
    char isLocked;
    int packetDataPtr;
    undefined4 packetId;
    undefined4 zero4_1;
    byte zeroByte;
    byte packetBuffer[20];
    int packetResult[2];

    packetDataPtr = *(int*)(thisPtr + 0x264); // +0x264: mReliableSendQueueHead
    int* connectionStatus = *(int**)(thisPtr + 0x180); // +0x180: mpConnectionStatus
    if (*(int*)(*connectionStatus + 0xd8) != 0) { // +0xd8: mIsSendingReliable
        isLocked = FUN_0071fa00(); // IsMutexLocked?
        if (isLocked != '\0') {
            packetDataPtr = *(int*)(thisPtr + 0x268); // +0x268: mReliableSendQueueTail
        }
    }
    if (packetDataPtr != 0) {
        FUN_00892af0(0); // LockMutex(0)
        FUN_00892a90(thisPtr, 1); // PrepareSend(this, 1)
        FUN_00894c40(packetDataPtr, packetBuffer); // ReadPacketData(packetDataPtr, packetBuffer)
        if (packetResult[0] != 0) {
            FUN_004daf90(packetResult); // FreePacketResult(packetResult)
        }
    }
    if (*(int*)(*connectionStatus + 0x40) == 0x637b907) { // Class ID check
        packetId = *(undefined4*)(thisPtr + 0x254); // +0x254: mReliablePacketId
        zero4_1 = 0;
        zeroByte = 0;
        FUN_00408a00(&packetId, 0); // SetPacketIdentity(&packetId, 0)
    }
    return;
}