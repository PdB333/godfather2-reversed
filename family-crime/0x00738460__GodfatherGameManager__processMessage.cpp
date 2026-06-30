// FUNC_NAME: GodfatherGameManager::processMessage
// Address: 0x00738460
// Handles various game messages (events) dispatched by the message system.
// Each message is identified by a 32-bit ID (first int in param_2 struct).
// Many messages involve entity handles that are converted by subtracting 0x48.

void __thiscall GodfatherGameManager::processMessage(uint thisPtr, int* pMsg)
{
    int* piVar1;
    undefined4* puVar2;
    char cVar3;
    undefined4 uVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int unaff_EBP;   // from caller's stack
    undefined4* unaff_ESI; // from caller's stack
    int* piVar8;
    undefined1* puVar9;
    undefined1 local_24[8];
    undefined** ppuStack_1c;

    iVar6 = *pMsg; // message ID
    if (iVar6 == DAT_0112fddc) {
        // Initialize/startup message
        uVar4 = *(undefined4*)(thisPtr + 0x2130); // some parameter
        piVar1 = (int*)(thisPtr - 0x3c); // base object pointer this - 0x3c
        iVar6 = thisPtr + 0x2110;
        piVar8 = piVar1;
        FUN_008e9cb0(0x369ac561, iVar6, piVar1, uVar4);
        FUN_008ece40(iVar6, piVar8, uVar4);
        (**(code**)(*piVar1 + 0x184))(thisPtr + 0x2120, 1);
        FUN_00460020(1);
        iVar6 = *piVar1;
        uVar4 = FUN_00421170(thisPtr + 0x2100);
        (**(code**)(iVar6 + 0xf0))(uVar4);
        (**(code**)(**(int**)(thisPtr + 0xf4) + 0x2c))();
        (**(code**)(*piVar1 + 0x70))();
        (**(code**)(**(int**)(thisPtr + 0xf4) + 0x2c))();
        FUN_004706f0(0);
        (**(code**)(*piVar1 + 0x134))(1);
        FUN_007fb040();
        FUN_0045f020(*(undefined4*)(thisPtr + 0x2134), *(undefined4*)(thisPtr + 0x2138), DAT_00d5ccf8, 0, 0);
        iVar6 = *(int*)(thisPtr + 0x708); // count
        iVar7 = 0;
        if (0 < iVar6) {
            do {
                iVar5 = FUN_00704110(iVar7);
                if (iVar5 != 0) {
                    FUN_004719a0();
                }
                iVar7 = iVar7 + 1;
            } while (iVar7 < iVar6);
        }
        FUN_004e0650(piVar1);
        FUN_005512c0(0);
        cVar3 = FUN_007f4800();
        if (cVar3 != '\0') {
            FUN_0072de20(piVar1);
            local_24[0] = 1;
            ppuStack_1c = &PTR_LAB_00e51890;
            FUN_0081dab0(&stack0xffffffcc);
            if (unaff_EBP != 0) {
                FUN_004daf90(&stack0xffffffd4);
            }
            if (unaff_ESI != (undefined4*)0x0) {
                do {
                    puVar2 = (undefined4*)unaff_ESI[1];
                    unaff_ESI[1] = 0;
                    *unaff_ESI = 0;
                    unaff_ESI = puVar2;
                } while (puVar2 != (undefined4*)0x0);
            }
        }
        *(uint*)(thisPtr + 0x1f1c) &= 0xf9ffffff;
        (**(code**)(*piVar1 + 0x14))();
        return;
    }
    if (iVar6 == DAT_0112fde8) {
        // Some update/tick message
        FUN_004088c0(thisPtr);
        return;
    }
    if (iVar6 == DAT_0112adb8) {
        // Message with entity handle (convert handle by -0x48)
        iVar6 = pMsg[1]; // data pointer
        if (*(int*)(iVar6 + 4) == 0) {
            FUN_0072ca00(0, iVar6 + 0xc);
        } else {
            FUN_0072ca00(*(int*)(iVar6 + 4) + -0x48, iVar6 + 0xc);
        }
        return;
    }
    if (iVar6 == DAT_0112dd08) {
        // Another entity-related message
        iVar6 = pMsg[1];
        iVar7 = iVar6;
        FUN_00716420(iVar6);
        cVar3 = FUN_00713200(iVar7);
        if (cVar3 != '\0') {
            (**(code**)(*(int*)(thisPtr - 0x3c) + 800))(iVar6); // vtable offset 800
        }
        return;
    }
    else {
        if (iVar6 == DAT_0112ade8) {
            iVar6 = pMsg[1];
            iVar5 = FUN_00471610();
            iVar7 = *(int*)(iVar6 + 4);
            if (iVar7 == 0) {
                iVar7 = 0;
            } else {
                iVar7 = iVar7 + -0x48;
            }
            FUN_0084b940(iVar7, iVar5 + 0x30, 5, 100, 0);
            puVar9 = local_24;
            FUN_00716420(puVar9);
            cVar3 = FUN_00713200(puVar9);
            if (cVar3 != '\0') {
                iVar6 = *(int*)(iVar6 + 4);
                if (iVar6 == 0) {
                    iVar6 = 0;
                } else {
                    iVar6 = iVar6 + -0x48;
                }
                FUN_0072e2d0(iVar6);
            }
            FUN_007133d0();
            return;
        }
        if (iVar6 == DAT_0112ada8) {
            if (*(int*)(pMsg[1] + 4) == 0) {
                FUN_0072e390(0);
            } else {
                FUN_0072e390(*(int*)(pMsg[1] + 4) + -0x48);
            }
            return;
        }
        if (iVar6 == DAT_0112adc0) {
            iVar6 = *(int*)(pMsg[1] + 0xc);
            if (iVar6 == 0) {
                iVar6 = 0;
            } else {
                iVar6 = iVar6 + -0x48;
            }
            iVar7 = *(int*)(pMsg[1] + 4);
            if (iVar7 == 0) {
                FUN_00732f80(0, iVar6);
            } else {
                FUN_00732f80(iVar7 + -0x48, iVar6);
            }
            return;
        }
        if (iVar6 == DAT_0112ade0) {
            if (*(int*)(pMsg[1] + 4) == 0) {
                FUN_0072e4a0(0);
            } else {
                FUN_0072e4a0(*(int*)(pMsg[1] + 4) + -0x48);
            }
            return;
        }
        if (iVar6 == DAT_0112adc8) {
            iVar6 = pMsg[1];
            if (*(int*)(iVar6 + 4) == 0) {
                FUN_0072c8f0(0, *(undefined1*)(iVar6 + 0xc));
            } else {
                FUN_0072c8f0(*(int*)(iVar6 + 4) + -0x48, *(undefined1*)(iVar6 + 0xc));
            }
            return;
        }
        if (iVar6 == DAT_0112b36c) {
            FUN_0072ce90();
            return;
        }
        if (iVar6 == DAT_0112a620) {
            // Compare object type or ID with current player/entity
            if (*(int*)(*(int*)(pMsg[1] + 4) + 0x38) == *(int*)(thisPtr + 0x20f8)) {
                *(undefined4*)(thisPtr + 0x20fc) = *(undefined4*)(pMsg[1] + 0xc);
                FUN_0072ee30();
            }
            return;
        }
        else {
            if (iVar6 == DAT_0112a5e0) {
                FUN_0072d530(pMsg[1]);
                return;
            }
            if (iVar6 == DAT_01206778) {
                // Handle entity remove/destroy
                if (*(int*)(pMsg[1] + 0xc) == 0) {
                    iVar6 = 0;
                } else {
                    iVar6 = *(int*)(*(int*)(pMsg[1] + 0xc) + 0x1c);
                }
                if (iVar6 == *(int*)(thisPtr + 0x1ea8)) {
                    FUN_004035f0(*(int*)(thisPtr + 0x1ea8), 0x10, -(uint)(thisPtr != 0x3c) & thisPtr);
                    *(undefined4*)(thisPtr + 0x1ea8) = 0;
                    FUN_007f9340(0, 0);
                }
            }
            if (DAT_012067dc == *pMsg) {
                // Shutdown/cleanup message
                if ((*(uint*)(thisPtr + 0x1f20) >> 0xf & 1) != 0) {
                    (**(code**)(*(int*)(thisPtr - 0x3c) + 0x1c4))(*(undefined4*)(thisPtr + 0x5c4));
                    *(uint*)(thisPtr + 0x1f20) &= 0xffff7fff;
                }
                FUN_0072ff10();
                if (*(undefined4**)(thisPtr + 0x20e8) != (undefined4*)0x0) {
                    (**(code**)**(undefined4**)(thisPtr + 0x20e8))(1);
                }
                *(undefined4*)(thisPtr + 0x20e8) = 0;
                if ((*(int*)(thisPtr + 0x213c) != 0) && (*(int*)(thisPtr + 0x213c) != 0x48)) {
                    FUN_00791d20(thisPtr - 0x3c);
                }
                FUN_00736340(0);
                if (((*(uint*)(thisPtr + 0x1f18) >> 8 & 1) != 0) && (*(int*)(thisPtr + 0x20f8) != 0)) {
                    FUN_006b0f70(*(int*)(thisPtr + 0x20f8), 0);
                }
                if ((*(byte*)(thisPtr + 0x1f23) & 1) != 0) {
                    if (thisPtr == 0x3c) {
                        iVar6 = 0;
                    } else {
                        iVar6 = thisPtr + 0x1ef4;
                    }
                    FUN_007ee320(iVar6);
                    *(uint*)(thisPtr + 0x1f20) &= 0xfeffffff;
                }
            }
            // Pass message to default handler
            FUN_00808540(pMsg);
            if (((DAT_012067dc == *pMsg) && (*(int*)(thisPtr + 0x213c) != 0)) &&
                (*(int*)(thisPtr + 0x213c) != 0x48)) {
                FUN_00790710(thisPtr - 0x3c);
            }
            iVar6 = *pMsg;
            if (DAT_0112add0 == iVar6) {
                iVar6 = FUN_00625050(0x8aeb8c80, 0);
                if (iVar6 != 0) {
                    *(uint*)(iVar6 + 0x74) |= 0x4000;
                }
                return;
            }
            else {
                if (iVar6 == DAT_0112e0fc) {
                    FUN_0072d7f0(pMsg[1] + 4);
                    return;
                }
                if (iVar6 == DAT_0112ad84) {
                    FUN_007320d0(*(undefined4*)(pMsg[1] + 4));
                }
            }
        }
    }
    return;
}