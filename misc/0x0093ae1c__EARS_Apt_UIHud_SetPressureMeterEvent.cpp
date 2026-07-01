// Xbox PDB: EARS_Apt_UIHud_SetPressureMeterEvent
// FUNC_NAME: PlayerDebugOptions::handleDebugCommand
void PlayerDebugOptions::handleDebugCommand(int commandId)
{
    char cVar1;
    int in_EAX;
    bool in_ZF;
    undefined4 in_stack_00000014;
    
    if (in_ZF) {
        cVar1 = FUN_0078af40(); // likely isWeakSpotBonusActive() or similar
        if (cVar1 != '\0') {
            FUN_005a04a0("ShowWeakSpotBonus"); // likely showDebugMessage or printToConsole
        }
        FUN_00939ee0(in_stack_00000014); // likely executeDebugCommand
        param_1 = DAT_011301e0; // some global debug flag or pointer
        FUN_00408a00(&param_1); // likely toggleDebugFlag
    }
    else {
        if (in_EAX == 2) {
            FUN_00939ee0(in_stack_00000014);
            FUN_005a04a0("DisableAutoHidePressureStr");
            param_1 = DAT_011302d0;
            FUN_00408a00(&param_1);
            return;
        }
        if (in_EAX == 3) {
            FUN_00939ee0(in_stack_00000014);
            FUN_005a04a0("EnableAutoHidePressureStr");
            FUN_005a04a0("HideWeakSpotBonus");
            param_1 = DAT_01130258;
            FUN_00408a00(&param_1);
            return;
        }
    }
    return;
}