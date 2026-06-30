// FUNC_NAME: EntityManager::findNearestEntityAtPosition
int EntityManager::findNearestEntityAtPosition(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
    undefined8 uVar1;
    int iVar2;
    undefined1 uVar3;
    char cVar4;
    int iVar5;
    byte *pbVar6;
    float10 fVar7;
    float local_b8;   // distance squared candidate
    float local_b4;   // movement length
    float local_b0;   // temp vector component
    float local_ac;   // temp vector component
    float local_a8;   // temp vector component
    undefined4 local_a4; // padding
    int local_9c;      // best candidate index
    int local_98;      // iterated index
    undefined4 local_94; // debug flag (1 or 2)
    undefined8 local_90; // current position
    float local_88;   // current Z?
    undefined8 local_84; // previous position
    float local_7c;   // previous Z?
    float local_78;   // deltaX
    float local_74;   // deltaY
    float local_70;   // deltaZ
    undefined4 local_68; // vector component
    undefined4 local_64; // padding
    undefined **local_60; // pointer to static data (likely function pointer table)
    undefined1 local_5c; // flag from FUN_007174e0
    float *local_58;   // pointer to internal target direction
    undefined8 *local_54; // pointer to previous position
    undefined8 *local_50; // pointer to current position
    float *local_4c;   // pointer to movement vector
    int local_48;      // this + 0x21cc (list pointer)
    int local_44;      // this pointer copy
    undefined4 *local_40; // pointer to debug var
    undefined4 local_3c; // debug flag copy
    undefined4 local_38; // param_5
    undefined4 local_34; // param_2
    undefined4 local_30; // param_3
    float local_2c;    // movement length
    float local_28;    // best distance candidate
    undefined4 local_24; // some flag
    undefined4 local_1c; // first time value
    undefined4 local_18; // second time value (if debug)
    
    local_9c = 0;
    local_b8 = 1e20f; // large initial distance (DAT_00d5f6f0)
    local_1c = FUN_0043b490(); // get some timestamp
    local_94 = 1;
    iVar5 = FUN_00800a90(); // check if debug enabled
    if (iVar5 != 0) {
        local_18 = FUN_0043b490(); // second timestamp
        local_94 = 2;
    }
    local_b4 = 0.0f;
    local_78 = 0.0f;
    local_74 = 0.0f;
    local_70 = 0.0f;
    
    iVar5 = FUN_00471610(); // get player entity
    // Read position from player entity (likely at offset 0x30 and 0x38)
    local_90 = *(undefined8 *)(iVar5 + 0x30); // x and y as double?
    local_88 = *(float *)(iVar5 + 0x38); // z?
    local_84 = local_90;
    local_7c = local_88;
    
    // If not in a specific state (0x48) or having a target?
    if ((*(int *)(this + 0x24c4) != 0) && (*(int *)(this + 0x24c4) != 0x48)) {
        iVar5 = FUN_00471610(); // get player entity again
        uVar1 = *(undefined8 *)(iVar5 + 0x30);
        local_88 = *(float *)(iVar5 + 0x38);
        local_90._0_4_ = (float)uVar1; // x
        local_b0 = (float)local_90 - (float)local_84; // delta x
        local_90._4_4_ = (float)((ulonglong)uVar1 >> 0x20); // y
        local_ac = local_90._4_4_ - local_84._4_4_; // delta y
        local_a8 = local_88 - local_7c; // delta z
        local_a4 = 0;
        local_90 = uVar1;
        fVar7 = (float10)FUN_0056afa0(&local_b0, &local_b0); // compute length of movement vector
        local_b4 = (float)fVar7;
        local_78 = local_b0;
        local_74 = local_ac;
        local_70 = local_a8;
    }
    
    uVar3 = FUN_007174e0(); // some flag
    local_b0 = *(float *)(this + 0x24dc); // internal target direction x
    local_ac = *(float *)(this + 0x24e0); // internal target direction y
    local_a8 = *(float *)(this + 0x24e4); // internal target direction z
    local_a4 = 0;
    fVar7 = (float10)FUN_0056afa0(&local_b0, &local_b0); // length of that vector
    local_6c = local_b0;
    local_68 = local_ac;
    local_64 = local_a8;
    if (fVar7 <= (float10)0.0f) {
        local_64 = 0;
        local_68 = 0;
        local_6c = 0.0f;
    }
    
    iVar5 = *(int *)(this + 0x21ec); // initial candidate (first entity to try)
    local_24 = 0;
    local_50 = &local_90; // current player position
    local_54 = &local_84; // previous player position
    local_58 = &local_6c; // internal target direction
    local_34 = param_2; // query x?
    local_48 = this + 0x21cc; // pointer to entity list head? or spatial hash root?
    local_4c = &local_78; // movement vector
    local_30 = param_3; // query y?
    local_40 = &local_1c; // debug timestamps
    local_38 = param_5; // query z?
    local_2c = local_b4; // movement length
    local_60 = &PTR_LAB_00d5fb08; // static data (possibly function table)
    local_44 = this;
    local_3c = local_94;
    local_28 = 1e20f; // DAT_00d5f6f0
    local_5c = uVar3;
    cVar4 = FUN_00717d00(); // another flag check
    local_24 = DAT_00d5fae8; // some global flag
    if (cVar4 == '\0') {
        local_24 = 0;
    }
    
    // Test the initial candidate (iVar5)
    cVar4 = FUN_006e7c30(iVar5, &local_60, &local_b8, &local_b4);
    if (cVar4 != '\0') {
        if (local_b8 < local_28) {
            local_28 = local_b8;
            local_9c = iVar5;
        }
        if (local_b8 < DAT_00e514c0) { // some threshold? return immediately if good enough
            return iVar5;
        }
    }
    
    // Spatial hash lookup: compute grid cell from player position
    iVar5 = ((int)(local_7c) >> 3 & 0x1fU) * 0x20 + ((int)(local_84._0_4_) >> 3 & 0x1fU);
    pbVar6 = &DAT_0112a960; // base of array of neighbor offsets (2-byte each)
    do {
        // Iterate over neighbors in the spatial hash
        // Index = (cell + offset) wrapped? Actually it combines pbVar6[0] and pbVar6[1] with iVar5
        int index = ((char)pbVar6[1] * 0x20 + iVar5 & 0x3e0U) | ((uint)*pbVar6 + iVar5 & 0x1f);
        for (iVar2 = *(int *)(local_98 + 0x20 + index * 8); iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)) {
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