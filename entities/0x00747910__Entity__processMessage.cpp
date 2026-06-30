// FUNC_NAME: Entity::processMessage
// Address: 0x00747910
// Role: Message handler for entity, processes custom message types 10-13.
// Fields: +0x54 (m_pComponentA), +0x5C (m_pRelatedObj), +0x60 (m_vPos), +0x68 (m_iDir), +0x6C (m_bFlag)

int __thiscall Entity::processMessage(Entity* thisObj, undefined4 param2, undefined4 param3, int msgType, undefined4 param5, undefined4 param6) {
    char bFlag;
    int iVar2;
    undefined4 result;
    undefined1* pStack;
    undefined4 uVar3;
    int localStack[3];
    undefined8 local14;
    int local_c;
    undefined1 local_8;
    undefined4 local_4;

    switch (msgType) {
        // case 10: handle some component operation
        case 10: {
            iVar2 = 0;
            if (thisObj->m_pComponentA != 0) {
                iVar2 = thisObj->m_pComponentA - 0x48; // treat as pointer to base?
            }
            uVar3 = getObjectFromPointer(iVar2); // FUN_00747790
            sendMessage(uVar3); // FUN_0044b210
            break;
        }
        // case 11: trigger effect with parameters
        case 11: {
            // calls vtable function at offset 0x2c with sound/effect ID and scaling
            (*(code**)(*(int*)thisObj + 0x2c))(0x35f5d58a, 1, 1, 0, 0x3f800000, 0x3f800000);
            return 1;
        }
        // case 12: update position/direction from related object
        case 12: {
            int* pRelated = thisObj->m_pRelatedObj; // +0x5C
            if ((pRelated != 0 && *(int*)(pRelated + 0x40) != 0) &&
                (iVar2 = *(int*)(pRelated + 0x40) - 0x48, iVar2 != 0) &&
                (bFlag = isComponentActive(iVar2, 0, 0), bFlag != 0)) { // FUN_00715cd0
                // Use current camera/player data
                iVar2 = getCurrentCamera(); // FUN_00471610
                *(undefined8*)(thisObj + 0x18) = *(undefined8*)(iVar2 + 0x30); // copy vector
                thisObj->m_iDir = *(int*)(iVar2 + 0x38);
                *(undefined1*)(thisObj + 0x1b) = 1;
                return 1;
            }
            // Fallback: use data from related object
            *(undefined8*)(thisObj + 0x18) = *(undefined8*)(pRelated + 0x48);
            iVar2 = *(int*)(pRelated + 0x50);
            *(undefined1*)(thisObj + 0x1b) = 0;
            thisObj->m_iDir = iVar2;
            return 1;
        }
        // case 13: build and send a message
        case 13: {
            local_c = 0;
            local14 = 0;
            localStack[1] = 0;
            localStack[2] = 0;
            local_8 = 0;
            local_4 = DAT_01205228; // global constant
            localStack[0] = -0x3e7f38d7; // message ID

            int* pRelated = thisObj->m_pRelatedObj;
            int iVar2;
            if (*(int*)(pRelated + 0x40) == 0) {
                iVar2 = 0;
            } else {
                iVar2 = *(int*)(pRelated + 0x40) - 0x48;
            }
            sendMessage(iVar2); // FUN_0044b210

            if ((char)thisObj->m_bFlag == 0) {
                local_c = thisObj->m_iDir;
                local14 = *(undefined8*)(thisObj + 0x18);
                local_8 = 1;
            }
            // Call through vtable of related object's component
            (*(code*)(**(int**)(pRelated + 0x1c)))(1);

            uVar3 = allocateBuffer(2); // FUN_008c6d20
            pStack = &stack0xffffffcc;
            packStructure(uVar3, pStack, 0); // FUN_0043c6f0

            if (localStack[0] != 0) {
                freeMessage(localStack); // FUN_004daf90
                return 1;
            }
            break;
        }
        default: {
            uVar3 = parentProcessMessage(param2, param3, param4, msgType, param5, param6); // FUN_004ac700
            return uVar3;
        }
    }
    return 1;
}