// FUNC_NAME: UIMenu::handleCommand (0x0096bb80 - UI menu navigation input handler)

void __fastcall UIMenu::handleCommand(UIMenu* this) {
    // +0xdc: current command/action type (enum)
    int actionType = *(int*)((char*)this + 0xdc);

    // Temporary string buffer (likely for debug logs)
    char* buffer = (char*)DAT_011301c0;
    int bufferLen = 0;

    // Clear buffer
    FUN_00408a00(&buffer, 0);

    switch (actionType) {
    case 1: {
        // +0x2ec: sub-controller for action type 1
        SubController* subCtrl = *(SubController**)((char*)this + 0x2ec);
        // vtable index 25 (offset 100) - some virtual method
        subCtrl->vtableMethod25((void*)((char*)this + 0xd4), *(int*)((char*)this + 0xc4));
        return;
    }
    case 2:
    case 3: {
        // +0x508: sub-controller for action types 2 and 3
        SubController* subCtrl = *(SubController**)((char*)this + 0x508);
        subCtrl->vtableMethod25((int*)((char*)this + 0xd4), *(int*)((char*)this + 0xc4));
        FUN_0095e7d0(*(int*)((char*)this + 0xc4) + *(int*)((char*)this + 0xd4));
        return;
    }
    case 4: {
        // +0x220: flag to allow this action
        if (*(char*)((char*)this + 0x220) != 0) {
            SubController* subCtrl = *(SubController**)((char*)this + 0x508);
            int* pArg1 = (int*)((char*)this + 0xd4);
            subCtrl->vtableMethod25(pArg1, *(int*)((char*)this + 0xc4));
            FUN_0095e7d0(*(int*)((char*)this + 0xc4) + *pArg1);
            int result = FUN_00962eb0();
            FUN_009643f0(*(int*)((char*)this + 0xc4) + *pArg1, result);
        }
        return;
    }
    default:
        // Debug log "MoveUp" with some format
        FUN_005a04a0("MoveUp", 0, &DAT_00d8cdec, 0);
        break;
    case 6: {
        // +0x378: sub-controller for action type 6
        SubController* subCtrl = *(SubController**)((char*)this + 0x378);
        subCtrl->vtableMethod25((void*)((char*)this + 0xd4), *(int*)((char*)this + 0xc4));
        return;
    }
    case 8: {
        // +0x63c: sub-controller for action type 8
        SubController* subCtrl = *(SubController**)((char*)this + 0x63c);
        subCtrl->vtableMethod25((int*)((char*)this + 0xd4), *(int*)((char*)this + 0xc4));
        FUN_0095e7d0(*(int*)((char*)this + 0xc4) + *(int*)((char*)this + 0xd4));
        return;
    }
    case 9: {
        // +0x590: sub-controller for action type 9
        SubController* subCtrl = *(SubController**)((char*)this + 0x590);
        subCtrl->vtableMethod25((int*)((char*)this + 0xd4), *(int*)((char*)this + 0xc4));
        uint index = *(int*)((char*)this + 0xc4) + *(int*)((char*)this + 0xd4);
        uint maxIndex = *(uint*)((char*)this + 0x638); // +0x638: array size limit
        if (maxIndex <= index) {
            FUN_0095e7d0(0);
        } else {
            // +0x5f8: array of ints (likely offsets or IDs)
            int* array = (int*)((char*)this + 0x5f8);
            FUN_0095e7d0(array[index]);
        }
        return;
    }
    case 0xb: {
        // +0x574: flag indicating whether submenu is active
        if (*(int*)((char*)this + 0x574) == 0) {
            // Global check at DAT_01129930 + 0x2b4
            if (*(int*)(DAT_01129930 + 0x2b4) != 0) {
                buffer = &DAT_00d8cdec;
                bufferLen = 0;
                FUN_005a04a0("MoveUp", 0);
                bufferLen = 0x96a724; // string literal address?
                FUN_009676f0();
                bufferLen = 0x96a72b;
                FUN_009679c0();
                bufferLen = 0;
                buffer = &DAT_00d8cdec;
                FUN_005a04a0("ShowWeaponsList", 0);
            }
        } else {
            // Global check at DAT_01129930 + 0x2b8
            if (*(int*)(DAT_01129930 + 0x2b8) != 0) {
                buffer = &DAT_00d8cdec;
                bufferLen = 0;
                FUN_005a04a0("MoveUp", 0);
                bufferLen = 0x96a769;
                FUN_00967a60();
                FUN_009676f0();
                return;
            }
        }
        return;
    }
    }
    return;
}