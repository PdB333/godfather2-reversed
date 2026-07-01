// Xbox PDB: EARS_Modules_PlayerGrappleSM_BuildStateMachineExecution
// FUNC_NAME: PlayerGrappleSM::setupAnimationTable

void PlayerGrappleSM::setupAnimationTable()
{
    // Register base animations for grappler state machine
    registerAnimation(0x7d);
    registerAnimation(0x40);
    registerAnimation(0x38);
    registerAnimation(0x6f);
    registerAnimation(0x39);

    // Set up state transition with looping (param 1 = loop, param 2 = blend?)
    registerStateTransition(0x6c, 1, 1);

    registerAnimation(0x48);
    registerAnimation(0x61);
    registerAnimation(0x44);
    registerAnimation(0x4e);
    registerAnimation(0x28);
    registerAnimation(0x67);

    // Transition with a global flag (probably used for controlling paired animation mode)
    registerStateTransitionWithGlobal(0x2e, _DAT_00d5c458, 1);

    registerAnimation(0x19);
    registerAnimationFromState(0x1a);
    registerAnimationFromState(0x49);

    // Register named animation strings for paired end states
    registerNamedAnimation("GrabEndPaired", 0x13);
    registerNamedAnimation("GrabEndPairedMasterOnly", 0x12);
    registerNamedAnimation("GrabEndPaired", 8);

    registerState(0x41);
    registerState(0x2f);
    registerState(0x27);
    registerState(0x4f);

    // Another transition with no looping (param 0 = no loop)
    registerStateTransitionWithFlag(0x6c, 0, 1);

    registerState(0x7e);
}