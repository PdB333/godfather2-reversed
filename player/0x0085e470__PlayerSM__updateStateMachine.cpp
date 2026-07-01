// FUNC_NAME: PlayerSM::updateStateMachine
void __fastcall PlayerSM::updateStateMachine(int this)
{
    int *piVar1;
    int iVar2;
    undefined4 uVar3;
    char *pcVar4;
    uint extraout_ECX;
    uint extraout_ECX_00;
    float10 fVar5;
    undefined4 uStack_20;
    undefined4 uStack_1c;
    undefined4 uStack_18;
    float fStack_14;
    float fStack_10;
    float fStack_c;
    float fStack_8;
    undefined1 uStack_4;
    
    // Check if state machine is valid and not in a special state (0x48 = 72, likely a state ID)
    if ((*(int *)(this + 8) != 0) && (*(int *)(this + 8) != 0x48)) {
        // Get the player object from the state machine
        if (*(int *)(this + 8) == 0) {
            iVar2 = 0;
        }
        else {
            iVar2 = *(int *)(this + 8) + -0x48;
        }
        
        // Check if the player is not in a certain state (bit 26 of flags at +0x249c)
        if ((*(uint *)(iVar2 + 0x249c) >> 0x1a & 1) == 0) {
            // Get the player object again
            if (*(int *)(this + 8) == 0) {
                iVar2 = 0;
            }
            else {
                iVar2 = *(int *)(this + 8) + -0x48;
            }
            
            // Get the current state's update function (vtable at +0x1f30, offset 8)
            uVar3 = (**(code **)(*(int *)(iVar2 + 0x1f30) + 8))();
            
            // Get various input/state values
            fVar5 = (float10)FUN_00549a00();  // Get some float value (likely time delta or input axis)
            fStack_14 = (float)fVar5;
            fVar5 = (float10)FUN_00549a10();  // Get another float
            fStack_10 = (float)fVar5;
            fVar5 = (float10)FUN_00549a20();  // Get another float
            fStack_8 = (float)fVar5;
            
            // Get boolean flags
            pcVar4 = (char *)FUN_00549a40((int)&uStack_20 + 3);  // Get some flag
            fStack_c = (float)(*pcVar4 != '\0');
            pcVar4 = (char *)FUN_00549a30((int)&uStack_20 + 3);  // Get another flag
            uStack_4 = *pcVar4 != '\0';
            
            // Update various state machine components
            FUN_0085e140(uVar3, &fStack_14);  // Update state transitions
            FUN_0085cf50(uVar3, &fStack_14);  // Update state behavior
            FUN_0085be80(uVar3, &fStack_14);  // Update state animations
            FUN_0085ce50(uVar3, &fStack_14);  // Update state physics
            
            // Get the input manager
            iVar2 = FUN_007ff880();  // GetInputManager()
            if ((iVar2 != 0) && (piVar1 = *(int **)(iVar2 + 0x130), piVar1 != (int *)0x0)) {
                uStack_18 = 0;
                uStack_1c = 0;
                
                // Handle input for movement (fStack_10 likely vertical input, fStack_c likely some modifier)
                if ((0.0 < fStack_10) && (fStack_c <= 0.0)) {
                    uStack_1c = _DAT_00d5780c;  // Some global input state
                }
                (**(code **)(*piVar1 + 0x4c))(0xeafab2ca, uStack_1c);  // Process input action
                
                // Handle sprint/run input
                if ((_DAT_00d577a0 < fStack_14) &&  // Threshold check
                   (fVar5 = (float10)(**(code **)(**(int **)(this + 4) + 0x1a8))(),  // Get some property
                   (float10)_DAT_00d7561c < fVar5)) {
                    uStack_20 = _DAT_00d5780c;  // Some global input state
                }
                (**(code **)(*piVar1 + 0x4c))(0xa84a846a, uStack_20);  // Process input action
            }
        }
        else {
            // Player is in a special state, reset input values
            FUN_00549a50(0);  // Set some float to 0
            FUN_00549a70(0x3f800000);  // Set some float to 1.0f
            FUN_00549ab0(1);  // Set some boolean to true
            FUN_00549ac0(extraout_ECX & 0xffffff00);  // Clear some flags
            FUN_00549a90(0);  // Set some value to 0
        }
        
        // Final update based on current state
        fVar5 = (float10)FUN_00549a10();  // Get current vertical input
        pcVar4 = (char *)FUN_00549a30((int)&uStack_20 + 3);  // Get some flag
        FUN_0085d290(*pcVar4 != '\0', (float10)0 < fVar5);  // Update state based on input
        return;
    }
    
    // State machine is invalid or in special state, reset everything
    FUN_00549a50(0);  // Set some float to 0
    FUN_00549a70(0);  // Set some float to 0
    FUN_00549ab0(1);  // Set some boolean to true
    FUN_00549ac0(extraout_ECX_00 & 0xffffff00);  // Clear some flags
    FUN_00549a90(0);  // Set some value to 0
    return;
}