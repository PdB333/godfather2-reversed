// Xbox PDB: EARS_Apt_UIOnlineMenu_ShowDonSitDownScreen
// FUNC_NAME: GameStateManager::setupState
void __fastcall GameStateManager::setupState(int *this)
{
    int *piVar1;
    int iVar2;
    code *pcVar3;
    undefined1 *puVar4;
    int iVar5;
    undefined1 *puVar6;
    undefined1 auStack_70[60];
    undefined4 uStack_34;

    // Call virtual function at vtable+8 (likely onEnter or similar)
    (**(code **)(*this + 8))();
    // Clear some global state
    FUN_00983120(0, 0, 0);
    // Check if multiplayer mode is active
    if (DAT_01223484 != 0) {
        // Initialize audio system
        FUN_008a30d0();
        // Set substate to 3
        this[0x79] = 3;
        uStack_34 = 3;
        // Setup audio state with substate
        FUN_008a3be0(auStack_70);
        iVar2 = this[0x37]; // current state
        if (iVar2 != 4) {
            // Reset counters
            this[0x31] = 0;
            this[0x35] = 0;
            // Determine next state value based on current state
            switch(iVar2) {
            case 1:
            case 6:
                iVar5 = 9;
                break;
            default:
                iVar5 = 10;
            }
            this[0x36] = iVar5;
            // If coming from state 1, do single-player setup
            if (iVar2 == 1) {
                FUN_0096adc0();
            }
            piVar1 = this + 4;
            // Register various event handlers
            FUN_005c02f0(piVar1, &LAB_00969090, 1);
            FUN_005c02f0(piVar1, &LAB_00963ee0, 1);
            FUN_005c02f0(piVar1, &LAB_0096fba0, 1);
            FUN_005c02f0(piVar1, &LAB_0096ccb0, 1);
            // Transition to state 4
            this[0x37] = 4;
            // Start the new state
            FUN_00965720();
        }
        // Send "Destroy" event
        FUN_005a04a0("Destroy", 0, &DAT_00d8cdec, 0);
        // Send "ShowSetUp" event
        FUN_005a04a0("ShowSetUp", 0, &DAT_00d8cdec, 0);
        // Call a function from a pointer at offset 0x142*4 + 0x6c
        pcVar3 = *(code **)(this[0x142] + 0x6c);
        *(undefined1 *)(this + 0x155) = 1; // set ready flag
        (*pcVar3)(0);
        // Unregister the event handlers
        FUN_005c0260(this + 4, &LAB_0096ee00, 1);
        // Determine two pointers for InitReadyState event
        puVar6 = &DAT_00e2f044;
        puVar4 = &DAT_00e2f044;
        if ((char)this[0x88] == '\0') {
            if (this[0xf2] == 2) {
                puVar4 = (undefined1 *)(*(int *)this[0xf1] + 0x20);
                puVar6 = (undefined1 *)(((int *)this[0xf1])[1] + 0x20);
            }
        }
        else if (this[0xcf] == 2) {
            puVar6 = (undefined1 *)(*(int *)this[0xce] + 0x20);
            puVar4 = (undefined1 *)(((int *)this[0xce])[1] + 0x20);
        }
        // Send "InitReadyState" event with the two pointers
        FUN_005a04a0("InitReadyState", 0, &DAT_00d8cdec, 2, puVar6, puVar4);
    }
    return;
}