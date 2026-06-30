// FUNC_NAME: TNLConnection::buildPacket
bool __thiscall TNLConnection::buildPacket(int param_1, int *param_2)
{
    int *piVar3;
    char cVar4;
    uint uVar5;
    int iVar6;
    int iVar8;
    int iVar9;
    uint uVar10;
    int iVar11;
    int local_4;
    int local_8;
    undefined4 *puVar1;
    undefined4 *puVar7;
    undefined4 *packetBase;
    int thisPtr;

    piVar3 = param_2;
    if (*(int *)(param_1 + 0x10) == 0) {
        return false;
    }
    iVar8 = param_2[3];
    iVar6 = *param_2;
    uVar10 = iVar8 * 0x20 + 0x10;
    iVar9 = 0;
    if ((*(uint *)(iVar6 + 4) & 0xff) < 10) {
        iVar11 = *(int *)(iVar6 + 0x20);
    } else {
        iVar11 = *(int *)(iVar6 + 0x28);
    }
    param_2 = (int *)uVar10;
    if ((-1 < iVar11) && (0 < iVar8)) {
        iVar9 = (iVar8 + 1) * 0x10;
        param_2 = (int *)(iVar9 + uVar10);
    }
    local_8 = 0;
    if ((*(uint *)(iVar6 + 4) & 0xff) < 10) {
        uVar5 = *(uint *)(iVar6 + 0x20);
    } else {
        uVar5 = *(uint *)(iVar6 + 0x28);
    }
    if (((uVar5 & 0x40000000) == 0) && (0 < piVar3[5])) {
        local_8 = piVar3[5] * 4 + 0x10;
        param_2 = (int *)((int)param_2 + local_8);
    }
    if (((uint)param_2 & 0xf) != 0) {
        iVar6 = 0x10 - ((uint)param_2 & 0xf);
        local_8._0_2_ = (short)local_8 + (short)iVar6;
        param_2 = (int *)((int)param_2 + iVar6);
    }
    cVar4 = alignAndGetOffset(param_2, &local_4); // FUN_0056e5e0
    if (cVar4 == '\0') {
        return false;
    }
    thisPtr = param_1; // extraout_ECX assumed same as param_1
    puVar7 = (undefined4 *)(*(int *)(thisPtr + 0x20) + local_4); // data buffer base
    puVar1 = *(undefined4 **)(thisPtr + 0x10); // packet header from pool
    puVar1[8] = puVar7; // set first data pointer
    *(short *)((int)puVar7 + 10) = (short)uVar10; // size of first chunk
    *puVar7 = 0; // clear flags?
    puVar7[1] = 0;
    *(undefined1 *)(puVar7 + 2) = 1; // flag byte
    *(undefined1 *)((int)puVar7 + 9) = 0;
    puVar7[3] = piVar3[3]; // count
    iVar6 = *piVar3;
    puVar7 = puVar7 + iVar8 * 8 + 4;
    if ((*(uint *)(iVar6 + 4) & 0xff) < 10) {
        iVar8 = *(int *)(iVar6 + 0x20);
    } else {
        iVar8 = *(int *)(iVar6 + 0x28);
    }
    if ((iVar8 < 0) || (piVar3[3] < 1)) {
        puVar1[9] = 0;
    } else {
        puVar1[9] = puVar7; // second data pointer
        *puVar7 = 0;
        puVar7[1] = 0;
        *(undefined1 *)(puVar7 + 2) = 1;
        *(undefined1 *)((int)puVar7 + 9) = 0;
        *(short *)((int)puVar7 + 10) = (short)iVar9;
        puVar7[3] = piVar3[3];
        puVar7 = (undefined4 *)((int)puVar7 + iVar9);
    }
    iVar8 = *piVar3;
    if ((*(uint *)(iVar8 + 4) & 0xff) < 10) {
        uVar10 = *(uint *)(iVar8 + 0x20);
    } else {
        uVar10 = *(uint *)(iVar8 + 0x28);
    }
    if (((uVar10 & 0x40000000) == 0) && (0 < piVar3[5])) {
        puVar1[10] = puVar7; // third data pointer
        *puVar7 = 0;
        puVar7[1] = 0;
        *(undefined1 *)(puVar7 + 2) = 1;
        *(undefined1 *)((int)puVar7 + 9) = 0;
        *(short *)((int)puVar7 + 10) = (short)local_8;
        puVar7[3] = piVar3[5];
    } else {
        puVar1[10] = 0;
    }
    undefined4 oldHead = *puVar1;
    puVar1[0xb] = (undefined4)param_2; // store aligned param_2
    *(undefined8 *)(puVar1 + 2) = *(undefined8 *)piVar3; // copy first two words of descriptor
    *(undefined8 *)(puVar1 + 4) = *(undefined8 *)(piVar3 + 2); // next two
    *(undefined8 *)(puVar1 + 6) = *(undefined8 *)(piVar3 + 4); // last two
    *(int *)(thisPtr + 0x1c) = *(int *)(thisPtr + 0x1c) - 1; // decrement pool count
    *(undefined4 *)(thisPtr + 0x10) = oldHead; // move pool head
    *puVar1 = 0; // clear link
    puVar1[1] = *(undefined4 *)(thisPtr + 0x18); // set previous link (last in list)
    if (*(int *)(thisPtr + 0x14) == 0) {
        *(undefined4 **)(thisPtr + 0x14) = puVar1; // list was empty, set head
    } else {
        **(undefined4 **)(thisPtr + 0x18) = puVar1; // link last node
    }
    *(int *)(thisPtr + 0x1030) = *(int *)(thisPtr + 0x1030) + 1; // increment total packet count
    *(undefined4 **)(thisPtr + 0x18) = puVar1; // update last pointer
    int channel = piVar3[1];
    int *channelHeadPtr = (int *)(thisPtr + 0x30 + channel * 4);
    int oldChannelHead = *channelHeadPtr;
    *(undefined4 **)channelHeadPtr = puVar1; // set channel head to new packet
    puVar1[0xd] = 0; // next in channel list (null if no old)
    if (oldChannelHead == 0) {
        puVar1[0xc] = 0; // previous in channel list null
    } else {
        *(undefined4 **)(oldChannelHead + 0x34) = puVar1; // old head's previous = new
        puVar1[0xc] = oldChannelHead; // new's next = old head
    }
    // TODO: These calls might be checksum/encryption
    FUN_0056f680();
    FUN_0056f6e0();
    FUN_0056f740();
    return true;
}