// FUNC_NAME: TNLConnection::processReliablePacket

void __thiscall TNLConnection::processReliablePacket(int thisPtr, int packetData)
{
    int *connectionMgr; // likely global connection manager
    int iVar2;
    char cVar3;
    int *piVar4;
    int iVar5;
    int iVar6;

    iVar2 = packetData;
    piVar4 = (int *)getConnectionManager(); // FUN_00655130 - returns singleton
    if ((piVar4 != (int *)0x0) && (piVar4[0x6d] == 4)) { // +0x1B4 state == 4 (connected)
        copyPacketHeader(0x20, &packetData); // FUN_0064b9e0 - copy 0x20 bytes from packetData to local?
        piVar4[0x28] = packetData; // +0xA0: lastReceivedSeq
        piVar4[0x24] = packetData; // +0x90: lastAckedSeq
        piVar4[0x2a] = packetData; // +0xA8: lastSentSeq?
        cVar3 = (**(code **)(*piVar4 + 0x2c))(); // virtual call at vtable+0x2c: isReady()
        if (cVar3 != '\0') {
            iVar5 = checkConnectionState(); // FUN_00655250 - returns 0 if connected?
            if (iVar5 == 0) {
LAB_006565bb:
                resetConnection(piVar4); // FUN_00655420
                unlockMutex(); // FUN_006550d0
                pcVar1 = *(code **)(*piVar4 + 0x14); // vtable+0x14: onDisconnect?
                piVar4[0x6d] = 7; // state = 7 (disconnected)
                (*pcVar1)();
                return;
            }
            iVar6 = getPacketQueue(thisPtr + 0x5c); // FUN_00658860 - returns queue at this+0x5c
            gPacketCount = gPacketCount - 1; // _DAT_01205a30
            if (*(uint *)(iVar6 + 4) < *(uint *)(iVar2 + 4)) { // compare sequence numbers
                sendPacket(thisPtr, iVar5); // FUN_006552f0
                goto LAB_006565bb;
            }
        }
        unlockMutex(); // FUN_006550d0
    }
    return;
}