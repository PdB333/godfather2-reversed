// FUNC_NAME: Navigation::findClosestNode
int Navigation::findClosestNode(int this, int param2, int param3, int param4, int param5)
{
    undefined8 uVar1;
    int iVar2;
    char uVar3;
    char cVar4;
    int iVar5;
    byte *pbVar6;
    float fVar7;
    float local_b8;
    float local_b4;
    float local_b0;
    float local_ac;
    float local_a8;
    undefined4 local_a4;
    int local_9c;
    int local_98;
    undefined4 local_94;
    undefined8 local_90;
    float local_88;
    undefined8 local_84;
    float local_7c;
    float local_78;
    float local_74;
    float local_70;
    float local_6c;
    undefined4 local_68;
    undefined4 local_64;
    undefined **local_60;
    char local_5c;
    float *local_58;
    undefined8 *local_54;
    undefined8 *local_50;
    float *local_4c;
    int local_48;
    int local_44;
    undefined4 *local_40;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    undefined4 local_30;
    float local_2c;
    float local_28;
    undefined4 local_24;
    undefined4 local_1c;
    undefined4 local_18;
    
    local_9c = 0;
    local_b8 = DAT_00d5f6f0; // Some large initial distance
    local_1c = FUN_0043b490(); // Get player position?
    local_94 = 1;
    iVar5 = FUN_00800a90(); // Check if something is active
    if (iVar5 != 0) {
        local_18 = FUN_0043b490(); // Get another position
        local_94 = 2;
    }
    local_b4 = 0.0;
    local_78 = 0.0;
    local_74 = 0.0;
    local_70 = 0.0;
    iVar5 = FUN_00471610(); // Get some manager
    local_90 = *(undefined8 *)(iVar5 + 0x30); // +0x30 position
    local_88 = *(float *)(iVar5 + 0x38); // +0x38 some float
    local_84 = local_90;
    local_7c = local_88;
    if ((*(int *)(this + 0x24c4) != 0) && (*(int *)(this + 0x24c4) != 0x48)) {
        iVar5 = FUN_00471610();
        uVar1 = *(undefined8 *)(iVar5 + 0x30);
        local_88 = *(float *)(iVar5 + 0x38);
        local_90._0_4_ = (float)uVar1;
        local_b0 = (float)local_90 - (float)local_84;
        local_90._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
        local_ac = local_90._4_4_ - local_84._4_4_;
        local_a8 = local_88 - local_7c;
        local_a4 = 0;
        local_90 = uVar1;
        fVar7 = (float10)FUN_0056afa0(&local_b0, &local_b0); // Vector length
        local_b4 = (float)fVar7;
        local_78 = local_b0;
        local_74 = local_ac;
        local_70 = local_a8;
    }
    uVar3 = FUN_007174e0(); // Get some flag
    local_b0 = *(float *)(this + 0x24dc); // +0x24dc node position X
    local_ac = *(float *)(this + 0x24e0); // +0x24e0 node position Y
    local_a8 = *(float *)(this + 0x24e4); // +0x24e4 node position Z
    local_a4 = 0;
    fVar7 = (float10)FUN_0056afa0(&local_b0, &local_b0); // Vector length
    local_6c = local_b0;
    local_68 = local_ac;
    local_64 = local_a8;
    if (fVar7 <= (float10)0) {
        local_64 = 0;
        local_68 = 0;
        local_6c = 0.0;
    }
    iVar5 = *(int *)(this + 0x21ec); // +0x21ec current node index
    local_24 = 0;
    local_50 = &local_90;
    local_54 = &local_84;
    local_58 = &local_6c;
    local_34 = param2;
    local_48 = this + 0x21cc; // +0x21cc some offset
    local_4c = &local_78;
    local_30 = param3;
    local_40 = &local_1c;
    local_38 = param5;
    local_2c = local_b4;
    local_60 = &PTR_LAB_00d5fb08; // Some function table
    local_44 = this;
    local_3c = local_94;
    local_28 = DAT_00d5f6f0;
    local_5c = uVar3;
    cVar4 = FUN_00717d00(); // Check some condition
    local_24 = DAT_00d5fae8;
    if (cVar4 == '\0') {
        local_24 = 0;
    }
    cVar4 = FUN_006e7c30(iVar5, &local_60, &local_b8, &local_b4); // Check node validity
    if (cVar4 != '\0') {
        if (local_b8 < local_28) {
            local_28 = local_b8;
            local_9c = iVar5;
        }
        if (local_b8 < DAT_00e514c0) {
            return iVar5;
        }
    }
    // Hash-based grid lookup
    iVar5 = ((int)local_7c >> 3 & 0x1fU) * 0x20 + ((int)(float)local_84 >> 3 & 0x1fU);
    pbVar6 = &DAT_0112a960; // Hash table
    do {
        for (iVar2 = *(int *)(local_98 + 0x20 + ((char)pbVar6[1] * 0x20 + iVar5 & 0x3e0U | (uint)*pbVar6 + iVar5 & 0x1f) * 8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)) {
            cVar4 = FUN_006e7c30(iVar2, &local_60, &local_b8, &local_b4);
            if (cVar4 != '\0') {
                if (local_b8 < DAT_00e514c0) {
                    return iVar2;
                }
                if (local_b8 < local_28) {
                    local_28 = local_b8;
                    local_9c = iVar2;
                }
            }
        }
        pbVar6 = pbVar6 + 2;
    } while ((int)pbVar6 < 0x112a99a);
    return local_9c;
}