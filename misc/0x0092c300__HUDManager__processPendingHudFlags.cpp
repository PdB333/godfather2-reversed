// FUNC_NAME: HUDManager::processPendingHudFlags
void __fastcall HUDManager::processPendingHudFlags(HUDManager* this)
{
    char cVar1;
    int iVar2;

    // Call virtual function at offset 0x2c from global singleton (likely update or pre-frame)
    (**(code**)(*DAT_01130000 + 0x2c))();

    // Only process if the HUD is not in a special state (e.g., menu open)
    if (*(int*)(this + 0x50) == 0) {
        // Flag at +0x184: e.g., show tutorial hint
        if (*(char*)(this + 0x184) != '\0') {
            iVar2 = getUIManager(); // FUN_0090a5a0
            if ((*(byte*)(iVar2 + 0x5f) & 1) == 0) {
                playTutorialSound(); // FUN_007915b0
                iVar2 = isTutorialEnabled(iVar2); // FUN_008c12a0
                if (iVar2 != 0) {
                    playUISound(); // FUN_008c8200
                    iVar2 = this + 0x14; // pointer to a list/container
                    addHudElement(iVar2, &LAB_005bfc10, 0); // FUN_005c0d50
                    addHudElement(iVar2, &LAB_0092bc60, 0);
                    addHudElement(iVar2, &LAB_005bfbe0, 0);
                }
            }
            *(undefined1*)(this + 0x184) = 0; // clear flag
        }
        // Flag at +0x185: e.g., show mission update
        if (*(char*)(this + 0x185) != '\0') {
            iVar2 = getUIManager(); // FUN_0090a5a0
            if ((iVar2 != 0) && (iVar2 = getLocalPlayer(), iVar2 != 0)) { // FUN_00791300
                getLocalPlayer(); // FUN_00791300 (again, maybe for state)
                cVar1 = isPlayerInRelevantState(); // FUN_00732fd0
                if (cVar1 != '\0') {
                    iVar2 = this + 0x14;
                    addHudElement(iVar2, &LAB_005bfc10, 0);
                    addHudElement(iVar2, &LAB_0092bce0, 0);
                    addHudElement(iVar2, &LAB_005bfbe0, 0);
                }
            }
            *(undefined1*)(this + 0x185) = 0; // clear flag
        }
    }
    return;
}