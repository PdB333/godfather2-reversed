// FUNC_NAME: CGameEventManager::handleEvent

void __thiscall CGameEventManager::handleEvent(int thisPtr, int eventData)
{
    char cVar1;
    undefined4 uVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    undefined4 uVar6;
    int *piVar7;
    int unaff_ESI;
    float10 fVar8;
    undefined4 uVar9;
    undefined4 local_10;
    undefined4 local_c;
    undefined1 local_8;
    int *piStack_4;

    iVar5 = eventData;

    // Check if bit 2 of offset 0x4d8 from thisPtr is clear
    if ((*(uint *)(thisPtr + 0x4d8) >> 2 & 1) == 0) {
        // Some global pointer check
        if (**(int **)(DAT_012233a0 + 4) == 0) {
            iVar3 = 0;
        } else {
            iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30;
        }
        if (*(int *)(eventData + 0xc) == 0) {
            iVar4 = 0;
        } else {
            iVar4 = *(int *)(eventData + 0xc) + -0x48;
        }
        if (iVar4 == iVar3) {
            // Probably a debug/log string
            local_10 = DAT_0112b18c;
            local_c = 0;
            local_8 = 0;
            FUN_00408a00(&local_10, 0);
        }
    }
    else if (((*(int *)(eventData + 0xc) == 0) || (*(int *)(eventData + 0xc) == 0x48)) ||
            (*(int *)(eventData + 0x30) != 2)) {
        // Check if event type is 3
        if (*(int *)(eventData + 0x30) == 3) {
            // Access a timer or global value via parent object (thisPtr - 0x7b0)
            fVar8 = (float10)(**(code **)(*(int *)(thisPtr + -0x7b0) + 0x1b0))();
            // Compare with global _DAT_00d7649c (likely a threshold)
            if ((((float10)_DAT_00d7649c < fVar8) &&
                (iVar3 = (**(code **)(*(int *)(thisPtr + -0x7b0) + 0x1e4))(), iVar3 != 0)) &&
                (piVar7 = (int *)FUN_0043b870(DAT_01130fa0), piVar7 != (int *)0x0)) {
                // Fire an event via vtable call at offset 0x28 with hash 0xbb77dc51
                (**(code **)(*piVar7 + 0x28))(0xbb77dc51, 1, 0xffffffff, 0);
            }
        }
    }
    else {
        // event type is 2 and eventData+0xc is valid (not 0 or 0x48)
        if (*(int *)(eventData + 0xc) == 0) {
            piVar7 = (int *)0x0;
        } else {
            piVar7 = (int *)(*(int *)(eventData + 0xc) + -0x48);
        }
        eventData = 0;
        // Query an object using hash 0x55859efa
        cVar1 = (**(code **)(*piVar7 + 0x10))(0x55859efa, &eventData);
        if ((cVar1 != '\0') && (eventData != 0)) {
            uVar6 = *(undefined4 *)(eventData + 0x1ed4);
            uVar9 = 1;
            uVar2 = FUN_00806440(1);
            FUN_008d8010(uVar6, uVar2, uVar9);
        }
    }

    // Additional check: event type 2 with valid data
    if (((*(int *)(iVar5 + 0x30) == 2) && (*(int *)(iVar5 + 0xc) != 0)) &&
       (*(int *)(iVar5 + 0xc) != 0x48)) {
        if (*(int *)(iVar5 + 0xc) == 0) {
            piVar7 = (int *)0x0;
        } else {
            piVar7 = (int *)(*(int *)(iVar5 + 0xc) + -0x48);
        }
        eventData = 0;
        // Query another hash 0x369ac561
        cVar1 = (**(code **)(*piVar7 + 0x10))(0x369ac561, &eventData);
        if (((cVar1 != '\0') && (piStack_4 != (int *)0x0)) &&
           (iVar5 = (**(code **)(*piStack_4 + 0x230))(), iVar5 != 0)) {
            if (iVar5 != unaff_ESI + -0x7b0) {
                iVar5 = FUN_006b1c70(iVar5, 0x55859efa);
                if (iVar5 == 0) {
                    return;
                }
                iVar5 = FUN_007ff880();
                if (iVar5 != unaff_ESI + -0x7b0) {
                    return;
                }
            }
            uVar2 = 0;
            uVar6 = FUN_006fbc40(0, 0);
            FUN_007f96a0(0x6210253, 0, uVar6, uVar2);
            FUN_006fbc70();
        }
    }
    return;
}