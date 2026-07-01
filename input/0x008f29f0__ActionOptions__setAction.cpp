// FUNC_NAME: ActionOptions::setAction
void __thiscall ActionOptions::setAction(int param_2, int param_3, int param_4)
{
    // Global pointer to game manager (e.g., GodfatherGameManager)
    char* gameManager = *(char**)0x01129814;
    
    // Check if player is active/controlled (byte at +0x15)
    if (gameManager[0x15] == '\0') {
        // Clear bit 2 (0x4) of flags at +0x10
        *(uint*)(this + 0x10) &= ~4;
    } else {
        // Call some setup function (e.g., enableAction)
        FUN_0068c590(0);
        // Set bit 2 of flags
        *(uint*)(this + 0x10) |= 4;
    }
    
    // Store action parameters
    *(int*)(this + 0x34) = param_4;   // +0x34: actionData
    *(int*)(this + 0x0C) = 9;         // +0x0C: actionType (9 = eAction_Interact?)
    *(int*)(this + 0x30) = param_3;   // +0x30: actionTarget
    FUN_00408680(&DAT_0112fe28);      // Some manager operation (e.g., beginAction)
    *(int*)(this + 0x1C) = param_2;   // +0x1C: actionSource
    FUN_004c0b90(&DAT_0112fe28, param_2, 0); // Register action with source
}