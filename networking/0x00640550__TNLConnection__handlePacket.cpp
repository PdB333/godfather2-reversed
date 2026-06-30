// FUNC_NAME: TNLConnection::handlePacket
// Address: 0x00640550
// Role: Process an incoming packet, update sequence numbers and packet window

void TNLConnection::handlePacket(int param_1, uint param_2, int param_3, int param_4)
{
    int *pPacketWindow;
    int *thisPtr;
    uint uVar2;
    int iVar3;
    undefined4 uVar4;
    int savedTopIndex;
    int savedBottomIndex;
    int *pWindowData;
    int local_28[3]; // temporary packet entry
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;
    undefined4 local_4;

    // +0x1C (in_EAX[7]) points to packet window structure
    pPacketWindow = (int *)this[7];
    FUN_0063def0(); // likely lock or begin critical section

    if (this[3] == 0x103) { // MAGIC_STATE_RECEIVE
        // Copy sequence number
        this[2] = this[1]; // +0x08 = +0x04
        if (this[5] == 0x11f) { // MAGIC_PACKET_TYPE
            iVar3 = FUN_00639c70(this + 4); // maybe getNextSequence
            this[3] = iVar3;
        } else {
            this[3] = this[5];
            this[4] = this[6];
            this[5] = 0x11f;
        }

        // Build temporary entry on stack
        local_18 = 1;
        local_28[1] = 0xffffffff;
        // +0x34 in pPacketWindow: some flag
        local_28[2] = pPacketWindow[0xd];
        local_1c = 0;
        // +0x14 in pPacketWindow: maybe packet size or type
        local_28[0] = pPacketWindow[5];
        // Push entry onto window stack: pPacketWindow[5] is stack pointer
        pPacketWindow[5] = (int)local_28;
        savedTopIndex = pPacketWindow[6];   // +0x18: top index
        pPacketWindow[7] = savedTopIndex;   // +0x1C: bottom index

        iVar3 = this[7];
        local_4 = 0;
        local_10 = 0xffffffff;
        // +0x34 in pPacketWindow: some other field
        local_c = *(undefined4 *)(iVar3 + 0x34);
        local_8 = 0;
        // +0x14 in pPacketWindow: linked list head
        local_14 = *(undefined4 *)(iVar3 + 0x14);
        // Update linked list head to point to stack entry
        *(undefined4 **)(iVar3 + 0x14) = &local_14;

        FUN_006417c0(); // process entry (maybe decode/decrypt)
        FUN_0063e400(); // flush or update

        // Restore indices
        pPacketWindow[7] = pPacketWindow[6];
        pWindowData = pPacketWindow + 8;
        FUN_00642880(pPacketWindow); // reset or cleanup
        thisPtr = pPacketWindow;
        if (param_4 != 0) {
            uVar4 = *(undefined4 *)(pPacketWindow[3] + 8); // +0x0C
            uVar2 = param_1 << 0x18 | 0x7fff9c;
            goto L_HANDLE_LOG;
        }
    } else {
        // Error: unexpected state
        uVar4 = FUN_00636c00("`%s\' expected", PTR_DAT_00e2a8c8);
        FUN_00638b80(uVar4);
        param_4 = unaff_EBX;
        pWindowData = thisPtr;
    }

    uVar4 = *(undefined4 *)(thisPtr[3] + 8);
    uVar2 = param_3 * 0x40 - 0xbfU | param_1 << 0x18 | 0x1d;

L_HANDLE_LOG:
    FUN_006438e0(uVar2, uVar4); // log or debug output

    // Write param_2 to some slot in a buffer based on index
    *(undefined4 *)(*(int *)(*thisPtr + 0x14) + -4 + thisPtr[6] * 4) = param_2;

    if (param_4 == 0) {
        iVar3 = thisPtr[3];
        *pWindowData = -1;
        FUN_006438e0(0x7fff94, *(undefined4 *)(iVar3 + 8));
        FUN_00642880(thisPtr);
    }

    if (savedTopIndex == thisPtr[6]) {
        // Window fully consumed
        thisPtr[7] = thisPtr[6];
        FUN_00642880(thisPtr);
        FUN_0063e400();
        return;
    }

    // Reorder/unpack remaining entries
    FUN_006426a0(thisPtr, savedTopIndex, 0xff, savedTopIndex, 0xff, savedTopIndex);
    FUN_0063e400();
    return;
}