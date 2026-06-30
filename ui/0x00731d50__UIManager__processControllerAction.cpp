// FUNC_NAME: UIManager::processControllerAction
void __fastcall UIManager::processControllerAction(int controllerIndex) {
    int* pManagerBase = *(int**)(DAT_012233a0 + 4);
    if (!pManagerBase) return;
    
    int* pPlayerData = (int*)((uint)pManagerBase - 0x1f30);
    if (!pPlayerData) return;
    
    int iVar2 = FUN_007ff880(); // likely getCurrentPlayerController()
    if (!iVar2) return;
    
    // Get a manager object from global resource
    int* vtable = (int*)FUN_0043b870(DAT_01131018);
    int iVar4 = (*(int (**)(void))(*vtable + 0x34))(); // e.g., getCurrentPlayerInfo()
    
    if (*(int*)(iVar4 + 0xc) == 0) {
        iVar4 = 0;
    } else {
        iVar4 = *(int*)(iVar4 + 0xc) - 0x48; // offset to player controller data
    }
    
    if (((*(uint*)(iVar2 + 0xc88) >> 0x10) & 1) == 0 &&
        ((*(uint*)(iVar2 + 0xc88) >> 0xf) & 1) == 0) {
        if (iVar4 == 0) {
            return;
        }
        if ((iVar4 != (int)pPlayerData) && (iVar4 != iVar2)) {
            return;
        }
        uStack_20 = 0x6bb4bf6c; // e.g., UI_MSG_CONFIRM
    } else {
        uStack_20 = 0x6d53d172; // e.g., UI_MSG_CANCEL
    }
    
    // Build event structure on stack
    aiStack_1c[4] = 0;
    aiStack_1c[3] = 0;
    aiStack_1c[2] = 0;
    ppuStack_24 = &PTR_FUN_00d5dbbc; // callback function pointer
    aiStack_1c[0] = 0;
    aiStack_1c[1] = 0;
    uStack_8 = 0;
    uStack_4 = DAT_01205228; // some context data
    
    FUN_0044b210(pPlayerData); // push event or queue
    
    uStack_30 = DAT_0112ad8c;
    pppuStack_2c = &ppuStack_24;
    uStack_28 = 0;
    
    if (controllerIndex == 0) {
        // Already zero
    } else {
        controllerIndex = controllerIndex + 0x3c; // offset into controller state
    }
    
    FUN_00408bf0(&uStack_30, controllerIndex, 0); // dispatch event with controller param
    
    if (aiStack_1c[0] != 0) {
        FUN_004daf90(aiStack_1c); // cleanup allocated event
    }
}