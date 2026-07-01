// FUNC_NAME: FUN_0089e440
void __thiscall FUN_0089e440(void* thisPtr, float* param_2, float* param_3) {
    char local_f5;
    int local_f4;
    undefined4 local_f0;
    float local_ec;
    undefined4 local_e8;
    undefined4 local_e4;
    float local_e0;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float local_d0;
    float fStack_cc;
    float fStack_c8;
    float fStack_c4;
    float local_c0;
    float local_bc;
    float local_b8;
    undefined4 local_b4;
    float local_b0;
    float local_ac;
    float local_a8;
    undefined4 local_a4;
    undefined4 local_a0;
    undefined4 local_9c;
    int local_90; // likely a vtable/function pointer
    undefined1 local_60[16]; // likely a matrix
    undefined4 local_50;
    undefined4 local_4c;
    undefined4 local_40;
    undefined4 local_20;

    // Decrement timer at +0xCC by a global delta time (DAT_012067e8)
    float fVar5 = *(float*)((int)thisPtr + 0xCC) - DAT_012067e8; 
    *(float*)((int)thisPtr + 0xCC) = fVar5;

    local_f0 = DAT_00d786d0; // some vector/quaternion constant?
    local_ec = DAT_00d5efa4; // likely a ground/height offset (0.0 or similar)

    if (fVar5 <= 0.0F) {
        // Timer expired, reset
        *(undefined4*)((int)thisPtr + 0xCC) = 0;
        *(undefined1*)((int)thisPtr + 0xD1) = 0; // flag/state byte
        
        local_e8 = local_f0;
        local_e4 = 0;
        local_f4 = (int)thisPtr;
        
        // Some global function - likely setting up a transform/rotation
        FUN_00a66df0(&local_f0, _DAT_00ef3a9c);

        // Traverse a linked list starting at +0x34
        int* piVar3 = *(int**)((int)thisPtr + 0x34);
        int iVar4 = 0; // result entity index?
        
        local_50 = _DAT_00d5780c; // some constant
        local_4c = 0xFFFFFFFF;
        local_20 = 0;
        local_40 = 0xFFFFFFFF;

        if (piVar3 != (int*)((int)thisPtr + 0x34)) {
            do {
                // Check entity type (piVar3[2] seems like an ID/type field)
                if (((piVar3[2] != 0) && (piVar3[2] != 0x1C)) && 
                    (cVar1 = FUN_00481620(), cVar1 != '\0')) {
                    
                    int entityBase;
                    if (piVar3[2] == 0) {
                        entityBase = 0;
                    } else {
                        entityBase = piVar3[2] + -0x1C; // offset to actual entity data
                    }
                    
                    // Set some flag at +0x48 to 0
                    *(undefined1*)(entityBase + 0x48) = 0;
                    
                    if (piVar3[2] == 0) {
                        entityBase = 0;
                    } else {
                        entityBase = piVar3[2] + -0x1C;
                    }
                    
                    // Calculate delta between param_2/param_3 and entity position (at +0x30,+0x34,+0x38,+0x3C)
                    local_e0 = *param_2 - *(float*)(entityBase + 0x30);
                    fStack_dc = param_2[1] - *(float*)(entityBase + 0x34);
                    fStack_d8 = param_2[2] - *(float*)(entityBase + 0x38);
                    fStack_d4 = param_2[3] - *(float*)(entityBase + 0x3C);
                    
                    local_d0 = *param_3 - *(float*)(entityBase + 0x30);
                    fStack_cc = param_3[1] - *(float*)(entityBase + 0x34);
                    fStack_c8 = param_3[2] - *(float*)(entityBase + 0x38);
                    fStack_c4 = param_3[3] - *(float*)(entityBase + 0x3C);
                    
                    // Subtract ground offset
                    local_bc = fStack_dc - DAT_00d5efa4;
                    local_ac = fStack_cc - DAT_00d5efa4;
                    
                    local_a0 = 0;
                    local_9c = 0;
                    local_b4 = 0;
                    local_a4 = 0;
                    local_c0 = local_e0;
                    local_b8 = fStack_d8;
                    local_b0 = local_d0;
                    local_a8 = fStack_c8;
                    
                    // Call some vtable function on local_90 (likely a method to test overlap/collision)
                    (**(code**)(local_90 + 0x20))(&local_f5, &local_c0, local_60);
                    
                    if (local_f5 != '\0') {
                        if (piVar3[2] == 0) {
                            iVar4 = 0;
                        } else {
                            iVar4 = piVar3[2] + -0x1C;
                        }
                    }
                }
                piVar3 = (int*)*piVar3; // next list node
            } while (piVar3 != (int*)(local_f4 + 0x34));
            
            if (iVar4 != 0) {
                // Mark the found entity as visible/set (flag at +0x48)
                *(undefined1*)(iVar4 + 0x48) = 1;
                *(undefined1*)(local_f4 + 0xD1) = 1; // also mark this object's flag
            }
        }
        FUN_00a66870(); // Cleanup?
    }
    return;
}