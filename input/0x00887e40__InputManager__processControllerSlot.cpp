// FUNC_NAME: InputManager::processControllerSlot
void __thiscall InputManager::processControllerSlot(int thisPtr, int slotIndex)
{
    char cVar1;
    int iVar2;
    undefined4 actionType;
    
    // Initialize slot with name
    ControllerSlot_init(slotIndex);
    
    // One-time global initialization of audio system
    if ((_DAT_0112e1c0 & 1) == 0) {
        _DAT_0112e1c0 = _DAT_0112e1c0 | 1;
        DAT_0112e1bc = AudioSystem_getStream(&PTR_LABEL_00d770b8);
    }
    
    // Get player entity for this controller slot
    iVar2 = PlayerManager_getPlayerForSlot(slotIndex, DAT_0112e1bc);
    
    // If player exists and has a valid entity handle and we haven't reached max tracked entities (10)
    if (((iVar2 != 0) && (*(int *)(iVar2 + 0x14) != 0)) && (*(uint *)(thisPtr + 0x78) < 10)) {
        // Store entity handle in slot array (+0x50 is entity handle array, +0x78 is count)
        *(int *)(thisPtr + 0x50 + *(uint *)(thisPtr + 0x78) * 4) = *(int *)(iVar2 + 0x14);
        *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x78) + 1;
    }
    
    // Start input processing loop
    InputSystem_beginProcessing(slotIndex, 0x108dea4e);
    cVar1 = InputSystem_isProcessing();
    while (cVar1 == '\0') {
        InputSystem_processNextEvent();
        actionType = InputSystem_getActionType();
        switch(actionType) {
        case 0: // Action pressed
            iVar2 = InputSystem_getEventData();
            *(bool *)(thisPtr + 0xad) = *(int *)(iVar2 + 8) != 0;
            break;
        case 1: // Action with position
            iVar2 = thisPtr + 0x268;
            InputSystem_getEventData(iVar2);
            InputSystem_getPositionData(iVar2);
            if (DAT_0120e93c != 0) {
                GameWindow_sendMessage(thisPtr + 0x3c, &DAT_0120e93c, 0x8000);
            }
            break;
        case 2: // Other actions
        case 3:
            InputSystem_getEventData();
        }
        InputSystem_finishEvent();
        cVar1 = InputSystem_isProcessing();
    }
    return;
}