// FUNC_NAME: UIWidget::handleMessage
undefined1 __thiscall UIWidget::handleMessage(int thisPtr, undefined4 param_2, undefined4 param_3, undefined4 param_4, int actionId, undefined4 param_6)
{
    uint *puVar1;
    byte bVar2;
    undefined1 result;
    uint uVar5;
    
    result = 1;
    switch(actionId + -10) {
    case 0: // actionId = 10
        if (*(int *)(thisPtr + 0x50) != 0) {
            void* context = getContext(); // FUN_006252f0
            showPanel1(context); // FUN_007f63e0
            return 1;
        }
        break;
    case 1: // actionId = 11
        if (*(int *)(thisPtr + 0x50) != 0) {
            void* context = getContext(); // FUN_006252f0
            hidePanel1(context); // FUN_007f6420
            return 1;
        }
        break;
    case 2: // actionId = 12
        if (*(int *)(thisPtr + 0x48) == 0) {
            // Call vtable method at offset 0x168 from some global base
            (**(code **)(iRam00000000 + 0x168))();
            return 1;
        }
        // Call vtable method on the object stored at 0x48, with a strange offset adjustment
        (**(code **)(*(int *)(*(int *)(thisPtr + 0x48) + -0x48) + 0x168))();
        return 1;
    case 3: // actionId = 13
        refreshView(); // FUN_0080e610
        return 1;
    case 4: // actionId = 14 - toggle on
        bVar2 = *(byte *)(*(int *)(thisPtr + 0x50) + 0x4a4);
        puVar1 = (uint *)(*(int *)(thisPtr + 0x50) + 0x4a4);
        *puVar1 = *puVar1 | 1;
        if ((~bVar2 & 1) != 0) {
            uVar5 = *(uint *)(thisPtr + 0x54);
            if ((uVar5 & 4) == 0) {
                *(uint *)(thisPtr + 0x54) = uVar5 | 6; // set bits 1 and 2
                return 1;
            }
            // else fall through to clear bit 2
LAB_0080e9b2:
            *(uint *)(thisPtr + 0x54) = uVar5 & 0xfffffffb;
            return 1;
        }
        break;
    case 5: // actionId = 15 - toggle off
        bVar2 = *(byte *)(*(int *)(thisPtr + 0x50) + 0x4a4);
        puVar1 = (uint *)(*(int *)(thisPtr + 0x50) + 0x4a4);
        *puVar1 = *puVar1 & 0xfffffffe;
        if ((~bVar2 & 1) == 0) {
            uVar5 = *(uint *)(thisPtr + 0x54);
            if ((uVar5 & 4) == 0) {
                *(uint *)(thisPtr + 0x54) = uVar5 & 0xfffffffd | 4; // clear bit 0, set bit 2
                return 1;
            }
            goto LAB_0080e9b2;
        }
        break;
    case 6: // actionId = 16
        doAction6(); // FUN_0080e5c0
        return 1;
    case 7: // actionId = 17
        doAction7(); // FUN_0080e5f0
        return 1;
    default:
        result = baseHandler(param_2, param_3, param_4, actionId, param_6); // FUN_004ac700
    }
    return result;
}