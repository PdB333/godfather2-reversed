// FUNC_NAME: TNLConnection::sendPendingPackets

int __fastcall TNLConnection::sendPendingPackets(TNLConnection* this)
{
    int iVar1;
    int iVar2;
    undefined *puVar3;

    lockMutex(); // FUN_00612a60 - likely mutex lock

    iVar1 = *(int *)(this + 0x10); // mSendState1
    if (iVar1 == *(int *)(this + 0x160)) // mExpectedState1A
    {
        iVar1 = sendReliablePacket(iVar1, *(undefined4 *)(this + 0x130), this + 0xe0, 8); // FUN_0060ab00
    }
    else
    {
        if ((iVar1 == *(int *)(this + 0x174)) && (iVar1 != 0)) // mExpectedState1B
        {
            if (*(int *)(this + 0x134) != 0) // mBuffer1
            {
                sendReliablePacket(iVar1, *(int *)(this + 0x134), this + 0xe0, 8);
            }
            if (*(int *)(this + 0x148) != 0) // mBuffer2
            {
                sendSequencedPacket(*(undefined4 *)(this + 0x10), *(int *)(this + 0x148), *(undefined4 *)(this + 0x128)); // FUN_0060b2f0
            }
            iVar1 = *(int *)(this + 0x15c); // mBuffer3
            if (iVar1 == 0) goto LAB_005366aa;
            puVar3 = (undefined *)(this + 0x110); // mBuffer4
            iVar2 = *(int *)(this + 0x10);
        }
        else if ((iVar1 == *(int *)(this + 0x178)) && (iVar1 != 0)) // mExpectedState1C
        {
            if (*(int *)(this + 0x138) != 0) // mBuffer5
            {
                sendUnreliablePacket(iVar1, *(int *)(this + 0x138), this + 0x100); // FUN_0060add0
            }
            if (*(int *)(this + 300) != 0) // mBuffer6 (offset 0x12c)
            {
                sendUnreliablePacket(*(undefined4 *)(this + 0x10), *(int *)(this + 300), this + 0xc0);
            }
            if (*(int *)(this + 0x154) != 0) // mBuffer7
            {
                sendUnreliablePacket(*(undefined4 *)(this + 0x10), *(int *)(this + 0x154), this + 0xd0);
            }
            if (*(int *)(this + 0x144) != 0) // mBuffer8
            {
                sendSequencedPacket(*(undefined4 *)(this + 0x10), *(int *)(this + 0x144), *(undefined4 *)(this + 0x128));
            }
            iVar1 = *(int *)(this + 0x158); // mBuffer9
            if (iVar1 == 0) goto LAB_005366aa;
            puVar3 = (undefined *)(this + 0x110);
            iVar2 = *(int *)(this + 0x10);
        }
        else
        {
            if ((iVar1 != gGlobalConnectionState) || (gGlobalConnectionBuffer == 0)) goto LAB_005366aa; // DAT_01219900, DAT_01219924
            puVar3 = &gGlobalBuffer; // DAT_011f6680
            iVar2 = iVar1;
            iVar1 = gGlobalConnectionBuffer;
        }
        iVar1 = sendUnreliablePacket(iVar2, iVar1, puVar3);
    }

LAB_005366aa:
    iVar2 = *(int *)(this + 0x14); // mSendState2
    if (iVar2 == *(int *)(this + 0x17c)) // mExpectedState2A
    {
        iVar1 = *(int *)(this + 0x120); // mSomeFlag
        if (*(int *)(this + 0x13c) != 0) // mBuffer10
        {
            iVar1 = flushSendBuffer(); // FUN_006063b0
            return iVar1;
        }
    }
    else if (iVar2 == gDefaultConnectionState) // DAT_012198f8
    {
        sendUnreliablePacket(iVar2, gDefaultConnectionBuffer, this + 0xc0); // DAT_0121991c
        iVar1 = *(int *)(this + 0x120);
        if (gDefaultConnectionFlag != 0) // DAT_01219910
        {
            iVar1 = flushSendBuffer();
            return iVar1;
        }
    }
    else
    {
        if (iVar2 == *(int *)(this + 0x16c)) // mExpectedState2B
        {
            iVar1 = sendSequencedPacket(iVar2, *(undefined4 *)(this + 0x140), *(undefined4 *)(this + 0x124));
            return iVar1;
        }
        if (iVar2 == *(int *)(this + 0x170)) // mExpectedState2C
        {
            sendSequencedPacket(iVar2, *(undefined4 *)(this + 0x14c), 0xffb);
            iVar1 = sendUnreliablePacket(*(undefined4 *)(this + 0x14), *(undefined4 *)(this + 0x150), this + 0xb0);
        }
    }
    return iVar1;
}