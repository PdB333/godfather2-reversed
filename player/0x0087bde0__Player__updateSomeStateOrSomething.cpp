// FUNC_NAME: Player::updateSomeStateOrSomething
undefined1 __fastcall Player::updateSomeState(int this) {
    undefined4 *puVar1;
    undefined1 uVar2;
    undefined4 uVar3;
    int iVar4;
    float fVar5;
    undefined **local_128;
    undefined4 local_124;
    int local_120;
    undefined4 local_11c;
    undefined8 local_118;
    undefined4 local_110;
    undefined1 local_10c;
    undefined4 local_108;
    undefined **local_104;
    undefined4 *local_100;
    int local_fc [16];
    undefined ***local_bc;
    undefined1 local_b8;
    undefined4 local_b4;
    undefined4 local_b0;
    undefined4 local_ac;
    undefined4 local_a8;
    undefined ***local_a4;
    undefined1 local_a0;
    undefined **local_9c;
    undefined **local_98;
    undefined4 local_94;
    undefined4 local_90;
    undefined4 local_8c;
    undefined4 local_88;
    undefined4 local_84;
    undefined4 local_80;
    undefined4 local_7c;
    undefined4 local_78;
    undefined4 local_74;
    undefined4 local_70;
    undefined4 local_6c;
    undefined4 local_68;
    undefined4 local_64;
    undefined4 local_60;
    undefined4 local_5c;
    undefined4 local_58;
    undefined4 local_54;
    float local_50;
    undefined4 local_4c;
    undefined4 local_48;
    undefined **local_44;
    undefined4 *local_40;
    int local_3c [15];

    // Initialize some locals
    local_fc[9] = 0;
    local_fc[10] = 0;
    local_fc[0xc] = 0;
    local_fc[0xd] = 0;
    local_fc[5] = 0;
    local_fc[4] = 0;
    local_fc[3] = 0;
    local_fc[8] = 0;
    local_fc[7] = 0;
    local_fc[6] = 0;
    local_ac = 0;
    local_b4 = 0;
    local_100 = (undefined4 *)0x0;
    local_104 = &PTR_FUN_00d76628;
    local_fc[0] = 0;
    local_fc[1] = 0;
    local_fc[2] = 0;
    local_fc[0xb] = 0;
    local_fc[0xe] = 0;
    local_b0 = DAT_00d5842c;
    uVar3 = FUN_008c9650(this, &local_b4, DAT_00e544cc, _DAT_00e544c0, 0);
    FUN_00876350(uVar3);
    if (local_3c[0] != 0) {
        FUN_004daf90(local_3c);
    }
    local_44 = &PTR_FUN_00e32808;
    while (local_40 != (undefined4 *)0x0) {
        puVar1 = (undefined4 *)local_40[1];
        local_40[1] = 0;
        *local_40 = 0;
        local_40 = puVar1;
    }
    fVar5 = DAT_00e544cc * DAT_00e544cc;
    local_9c = &PTR_FUN_00d76674;
    local_94 = 0;
    local_98 = &PTR_FUN_00d76628;
    local_90 = 0;
    local_8c = 0;
    local_88 = 0;
    local_6c = 0;
    local_68 = 0;
    local_64 = 0;
    local_60 = 0;
    local_5c = 0;
    local_58 = 0;
    local_7c = 0;
    local_80 = 0;
    local_84 = 0;
    local_70 = 0;
    local_74 = 0;
    local_78 = 0;
    local_fc[0xc] = _DAT_00d5c458;
    local_fc[0xd] = DAT_00d5ef70;
    FUN_00876350(&local_104);
    local_54 = DAT_00d5ef70;
    local_4c = DAT_00d5ca18;
    local_a4 = &local_9c;
    local_48 = DAT_00d76470;
    local_a8 = DAT_0112d9e4;
    local_a0 = 0;
    local_50 = fVar5;
    FUN_00408a00(&local_a8, 0);
    iVar4 = FUN_00471610();
    local_124 = 0x45aaf5f7;
    if ((*(uint *)(this + 0xc88) >> 2 & 1) != 0) { // Check some flag at offset 0xc88
        local_124 = 0xff44458b;
    }
    if ((*(int *)(this + 0x2b0) == 0) || // Check some pointer at offset 0x2b0
       (local_120 = *(int *)(this + 0x2b0) + -0x48, local_120 == 0)) {
        local_120 = this;
    }
    local_128 = &PTR_FUN_00d5dbbc;
    if (local_120 == 0) {
        local_120 = 0;
    }
    else {
        local_120 = local_120 + 0x48; // Adjust pointer by 0x48
    }
    local_11c = 0;
    if (local_120 != 0) {
        local_11c = *(undefined4 *)(local_120 + 4);
        *(int **)(local_120 + 4) = &local_120;
    }
    local_108 = DAT_01205228;
    local_10c = 1;
    local_118 = *(undefined8 *)(iVar4 + 0x30);
    local_110 = *(undefined4 *)(iVar4 + 0x38);
    local_bc = &local_128;
    local_fc[0xf] = DAT_0112ad8c;
    local_b8 = 0;
    FUN_00408a00(local_fc + 0xf, 0);
    uVar2 = FUN_00880600(this);
    if (local_120 != 0) {
        FUN_004daf90(&local_120);
    }
    local_128 = &PTR_LAB_00e2f0c0;
    FUN_00874970();
    if (local_fc[0] != 0) {
        FUN_004daf90(local_fc);
    }
    while (local_100 != (undefined4 *)0x0) {
        puVar1 = (undefined4 *)local_100[1];
        local_100[1] = 0;
        *local_100 = 0;
        local_100 = puVar1;
    }
    return uVar2;
}