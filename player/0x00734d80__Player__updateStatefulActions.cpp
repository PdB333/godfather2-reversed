// FUNC_NAME: Player::updateStatefulActions
void __thiscall Player::updateStatefulActions(void* thisPtr, int param_2, char param_3)
{
    float fVar1;
    char cVar2;
    int uVar3;
    int iVar4;
    int* piVar5;
    int uVar6;
    int uStack_68;
    undefined*** pppuStack_64;
    char uStack_60;
    int uStack_58;
    undefined*** pppuStack_54;
    char uStack_50;
    undefined** ppuStack_48;
    int iStack_44;
    int iStack_40;
    int uStack_3c;
    int uStack_38;
    int uStack_34;
    int uStack_30;
    char uStack_2c;
    float fStack_28;
    undefined** ppuStack_24;
    int uStack_20;
    int iStack_1c;
    int uStack_18;
    int uStack_14;
    int uStack_10;
    int uStack_c;
    char uStack_8;
    float fStack_4;
    
    // If the entity ID at param_2+0x2138 doesn't match the player's stored ID
    if (*(int*)(param_2 + 0x2138) != thisPtr[0x84e]) {
        cVar2 = ((int (__thiscall *)(void*))(*thisPtr + 0x1bc))();  // vtable call
        if ((cVar2 != 0) && ((*(unsigned int*)(param_2 + 0x1f54) >> 8 & 1) != 0)) {
            // Log some hash event
            uVar6 = 0;
            uVar3 = beginLogScope(0, 0);
            logMessage(0xb988cf08, 0, uVar3, uVar6);
            endLogScope();
        }
    }
    
    iVar4 = getSomeGameState();
    if (param_3 == 0) {
        iStack_44 = (-(unsigned int)(iVar4 != 0) & 0xb4fcc3cd) + 0xd4902a68;
    } else {
        iStack_44 = (-(unsigned int)(iVar4 != 0) & 0x8fa17cd) + 0x6cb936fe;
    }
    
    iVar4 = param_2 + 0x48;
    // Initialize a stack-based linked list node (scope structure)
    uStack_30 = 0;
    uStack_34 = 0;
    uStack_38 = 0;
    ppuStack_48 = &scopedActionVTable;
    iStack_40 = 0;
    uStack_3c = 0;
    uStack_2c = 0;
    fStack_28 = 0.0f;  // DAT_01205228
    
    if (iVar4 != 0) {
        uStack_3c = *(int*)(param_2 + 0x4c);  // save old next pointer
        *(int**)(param_2 + 0x4c) = &iStack_40;  // insert new node
        iStack_40 = iVar4;
    }
    
    piVar5 = thisPtr + 0xf;  // offset to some data
    pppuStack_64 = &ppuStack_48;
    uStack_68 = 0x112ad8c;   // some constant hash
    uStack_60 = 0;
    initScopedStructure(&uStack_68, piVar5, 0);
    
    if (param_3 != 0) {
        // Another scope for active state
        ppuStack_24 = &scopedActionVTable;
        uStack_c = 0;
        uStack_10 = 0;
        uStack_14 = 0;
        iStack_1c = 0;
        uStack_18 = 0;
        uStack_8 = 0;
        fStack_4 = 0.0f;
        uStack_20 = 0xaafd93f7;  // another hash
        if (iVar4 != 0) {
            uStack_18 = *(int*)(param_2 + 0x4c);
            *(int**)(param_2 + 0x4c) = &iStack_1c;
            iStack_1c = iVar4;
        }
        pppuStack_54 = &ppuStack_24;
        uStack_58 = 0x112ad8c;
        uStack_50 = 0;
        initScopedStructure(&uStack_58, piVar5, 0);
        if (iStack_1c != 0) {
            destroyScopedStructure(&iStack_1c);
        }
    }
    
    iVar4 = thisPtr[0x961];  // pointer to current target/vehicle (0x2584)
    if (((iVar4 != 0) && (iVar4 != 0x48)) && (param_3 != 0) &&
        ((iVar4 = *(int*)(iVar4 + 0xc), 0x13 < iVar4 && ((iVar4 < 0x16 || (iVar4 == 0x24)))))) {
        // Overwrite action with a specific hash if in certain combat states
        pppuStack_54 = &ppuStack_48;
        iStack_44 = 0x3a85b789;
        uStack_58 = 0x112ad8c;
        uStack_50 = 0;
        initScopedStructure(&uStack_58, piVar5, 0);
    }
    
    if (iStack_40 != 0) {
        destroyScopedStructure(&iStack_40);
    }
    
    uVar3 = getPlayerMode();
    cVar2 = checkPlayerModeFlag(param_2, uVar3);
    if (cVar2 == 0) {
        piVar5 = (int*)getSingletonByHash(0x1131040);  // e.g., CombatManager
        if ((piVar5 != (int*)0x0) && (piVar5[7] != 0) && (piVar5[7] != 0x48)) {
            cVar2 = ((int (__thiscall *)(int, int))(*piVar5 + 0x1c))(0x100);  // vtable call
            if (cVar2 != 0) {
                iVar4 = getPlayerStateEnum();
                if (iVar4 == 2) {
                    uVar6 = 0;
                    uVar3 = beginLogScope(0, 0);
                    logMessage(0xd13d7685, 0, uVar3, uVar6);
                } else {
                    iVar4 += -3;
                    if (iVar4 != 0) goto LAB_00735044;
                    uVar3 = beginLogScope(0, 0);
                    logMessage(0x78a8d60f, 0, uVar3, iVar4);
                }
                endLogScope();
            }
        }
    }
    
LAB_00735044:
    if ((((*(unsigned int*)(param_2 + 0x8e0) >> 10 & 1) != 0) &&
        (iVar4 = *(int*)(param_2 + 0x74c), iVar4 != 0)) && (iVar4 != 0x48)) {
        cVar2 = *(char*)(iVar4 + 0x160);
        if (((cVar2 == 1) || (cVar2 == 2)) || ((*(unsigned int*)(iVar4 + 0x188) >> 2 & 1) != 0)) {
            handleVehicleCollision(param_2, CONCAT31((int3)((unsigned int)iVar4 >> 8), cVar2));
        }
    }
    
    piVar5 = (int*)getSingletonByHash(0x1131018);  // e.g., InputManager
    if (piVar5 != (int*)0x0) {
        iVar4 = ((int (__thiscall *)(int*))(*piVar5 + 0x34))();  // vtable call
        if (iVar4 != 0) {
            iVar4 = ((int (__thiscall *)(int*))(*piVar5 + 0x34))();  // get some state
            if (*(int*)(iVar4 + 0x30) == 2) {
                fVar1 = (float)*(int*)(iVar4 + 0x40);
                if (*(int*)(iVar4 + 0x40) < 0) {
                    fVar1 += 0.0f;  // DAT_00e44578 (likely 0.0f)
                }
                if (0.0f < fVar1 * 0.0f +  0.0f) {  // DAT_00d5efb8 and _DAT_00d5780c are scaling factors?
                    uVar6 = 0;
                    uVar3 = beginLogScope(0, 0);
                    logMessage(0, 0, uVar3, uVar6);
                    endLogScope();
                }
            }
        }
    }
    return;
}