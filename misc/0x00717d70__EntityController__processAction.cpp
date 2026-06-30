// FUNC_NAME: EntityController::processAction
void __thiscall EntityController::processAction(int thisPtr, int component) {
    char cVar1;
    int iVar2;
    int *piVar3;
    int iVar4;
    int iVar5;
    float10 fVar6;
    int local_44;
    uint4 uStack_40;
    uint4 *pppuStack_3c;
    byte1 uStack_38;
    int aiStack_34 [4];
    uint4 *local_24;
    uint4 local_20;
    int local_1c;
    uint4 local_18;
    uint4 local_14;
    uint4 local_10;
    uint4 local_c;
    byte1 local_8;
    uint4 local_4;
    
    // Check if component has a child object (at offset 0xc)
    if (*(int *)(component + 0xc) == 0) {
        iVar4 = 0;
    } else {
        iVar4 = *(int *)(component + 0xc) + -0x48;
    }
    
    // Proceed only if component has data and its size is not 0x48
    if ((*(int *)(component + 4) != 0) && (*(int *)(component + 4) != 0x48)) {
        // If component type is 3 (e.g., interactive type)
        if (*(int *)(component + 0x30) == 3) {
            if (*(int *)(component + 4) == 0) {
                piVar3 = (int *)0x0;
            } else {
                piVar3 = (int *)(*(int *)(component + 4) + -0x48);
            }
            local_44 = 0;
            // Virtual call with hash - likely a query interface
            cVar1 = (**(code **)(*piVar3 + 0x10))(0xa5975eb2, &local_44);
            if (((cVar1 != '\0') && (local_44 != 0)) &&
               (cVar1 = getEnumList(aiStack_34, 4), cVar1 != '\0')) {
                iVar5 = 0;
                iVar2 = getEnumCount();
                if (0 < iVar2) {
                    do {
                        if (3 < iVar5) break;
                        if (aiStack_34[iVar5] != 0) {
                            iVar4 = aiStack_34[iVar5];
                            break;
                        }
                        iVar5 = iVar5 + 1;
                        iVar2 = getEnumCount();
                    } while (iVar5 < iVar2);
                }
            }
        }
        if (iVar4 != 0) {
            // Prepare a message structure 
            local_c = 0;
            local_10 = 0;
            local_14 = 0;
            local_24 = &PTR_FUN_00d5dbbc; // likely a vtable for the message
            local_1c = 0;
            local_18 = 0;
            local_8 = 0;
            local_4 = DAT_01205228; // global data
            local_20 = 0x8b284db6; // message ID
            
            if (iVar4 + 0x48 != 0) {
                local_18 = *(uint4 *)(iVar4 + 0x4c);
                *(int **)(iVar4 + 0x4c) = &local_1c;
                local_1c = iVar4 + 0x48;
            }
            uStack_40 = DAT_0112ad8c;
            pppuStack_3c = &local_24;
            uStack_38 = 0;
            if (*(int *)(thisPtr + 0xc) == 0) {
                iVar2 = 0;
            } else {
                iVar2 = *(int *)(thisPtr + 0xc) + 0x3c;
            }
            // Send event to target
            sendEvent(&uStack_40, iVar2, 0);
            
            iVar2 = isComponentActive(iVar4);
            if (iVar2 != 0) {
                // Apply force to the component's child
                applyForce(*(uint4 *)(component + 0x2c), DAT_01205228);
                fVar6 = (float10)(**(code **)(**(int **)(thisPtr + 0xc) + 0xbc))(iVar4);
                if (fVar6 != (float10)0) {
                    setComponentState(iVar4, 9);
                }
            }
            if (local_1c != 0) {
                removeFromLinkedList(&local_1c);
            }
        }
    }
    // Check if a specific bit (bit 14 of a field at this+0xc+0x8e4) is set
    if ((*(uint *)(*(int *)(thisPtr + 0xc) + 0x8e4) >> 0xe & 1) != 0) {
        activateEntity(*(uint4 *)(thisPtr + 0x3c));
    }
    return;
}