// Xbox PDB: EARS_Modules_CheckpointManager_FailActiveCheckpoint
// FUNC_NAME: GodfatherGameManager::sendBloodAccomplishment
void __thiscall GodfatherGameManager::sendBloodAccomplishment(int thisPtr, uint param2, uint param3)
{
    int* piVar1;
    undefined1* puVar2;
    int iVar3;
    int* piVar4;
    uint local_94;
    int local_90;
    uint local_8c;
    int* local_88;
    int local_84[5];
    undefined1* local_70[3];
    code* local_64;
    undefined1 local_60[16];
    undefined4 local_50;
    undefined4 uStack_4c;
    undefined4 uStack_48;
    undefined4 uStack_44;
    undefined4 local_40;
    undefined4 uStack_3c;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined4 local_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined4 local_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    undefined4 uStack_14;

    // +0x18: unknown field, likely some state or pointer
    *(uint*)(thisPtr + 0x18) = param2;

    // FUN_004d3d90: likely a string copy or conversion (param3 is string?)
    FUN_004d3d90(param3);

    // Build formatted string: "%04X.%04X" from two shorts at (this+0x1c)+0x70 and +0x74
    // this+0x1c points to a session/connection object
    FUN_004d4a60(local_70, 1, "%04X.%04X",
                 *(ushort*)(*(int*)(thisPtr + 0x1c) + 0x70),
                 *(ushort*)(*(int*)(thisPtr + 0x1c) + 0x74));

    puVar2 = local_70[0];
    if (local_70[0] == (undefined1*)0x0) {
        puVar2 = (undefined1*)&DAT_0120546e; // default string
    }

    // Send a packet with tags 0x53504750 ('SPGP') and 0x43484b46 ('CHKF')
    FUN_009085a0(0x53504750, 0x43484b46, puVar2);

    // Get global network manager singleton (FUN_004262f0(0))
    iVar3 = FUN_004262f0(0);

    // Copy 64 bytes of matrix/transform data from offset 0x40 in the manager
    local_50 = *(undefined4*)(iVar3 + 0x40);
    uStack_4c = *(undefined4*)(iVar3 + 0x44);
    uStack_48 = *(undefined4*)(iVar3 + 0x48);
    uStack_44 = *(undefined4*)(iVar3 + 0x4c);
    local_40 = *(undefined4*)(iVar3 + 0x50);
    uStack_3c = *(undefined4*)(iVar3 + 0x54);
    uStack_38 = *(undefined4*)(iVar3 + 0x58);
    uStack_34 = *(undefined4*)(iVar3 + 0x5c);
    local_30 = *(undefined4*)(iVar3 + 0x60);
    uStack_2c = *(undefined4*)(iVar3 + 0x64);
    uStack_28 = *(undefined4*)(iVar3 + 0x68);
    uStack_24 = *(undefined4*)(iVar3 + 0x6c);
    local_20 = *(undefined4*)(iVar3 + 0x70);
    uStack_1c = *(undefined4*)(iVar3 + 0x74);
    uStack_18 = *(undefined4*)(iVar3 + 0x78);
    uStack_14 = *(undefined4*)(iVar3 + 0x7c);

    // Initialize packet list header
    local_84[1] = 0;
    local_84[2] = 0;
    local_84[3] = 0;
    local_84[4] = _DAT_00d5780c;

    local_94 = DAT_0112fed4;
    local_90 = 0;
    local_8c = local_8c & 0xffffff00; // clear lower byte (status flag?)

    // Initialize packet header (0 = reset?)
    FUN_00408a00(&local_94, 0);

    local_88 = &local_84[1]; // point to second element (likely next pointer)
    local_8c = 0xffffffff;   // set flags
    local_94 = 5;            // packet type ID (accomplishment blood)
    local_90 = iVar3;        // network manager pointer

    // Log the blood accomplishment event
    FUN_004eacb0("accomp_blood");

    // Build packet: head list, output buffer, data, max size 511, alignment 4, type info
    piVar4 = (int*)FUN_004df3c0(local_84, local_60, &local_50, 0x1ff, 4, &local_94);

    // Manage outgoing packet linked list at this+0x2c
    piVar1 = (int*)(thisPtr + 0x2c);
    if (*(int*)(thisPtr + 0x2c) != 0) {
        // Clear next pointer of current head
        *(undefined4*)(*(int*)(thisPtr + 0x2c) + 8) = 0;
        *piVar1 = 0;
    }

    // Insert new packet at head of list
    iVar3 = *piVar4;
    *piVar1 = iVar3;
    if (iVar3 != 0) {
        *(int**)(iVar3 + 8) = piVar1; // set next pointer to previous head
        *piVar4 = 0;
    }

    // Clear next of old head (if any)
    if (local_84[0] != 0) {
        *(undefined4*)(local_84[0] + 8) = 0;
    }

    *(undefined4*)(thisPtr + 0x40) = 0; // clear some field

    // Flush send buffer
    FUN_00911fd0();

    // Debug output
    FUN_00408680(&DAT_012069b4);

    // Free formatted string (local_70[0]) via destructor function pointer
    if (local_70[0] != (undefined1*)0x0) {
        (*local_64)(local_70[0]);
    }

    return;
}