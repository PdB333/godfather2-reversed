// Xbox PDB: EARS_Modules_PlayerGrappleSM_BuildStateMachineGrabIdle
// FUNC_NAME: PlayerGrappleSM::registerAnimationEvents
void PlayerGrappleSM::registerAnimationEvents()
{
    // Set state priorities / transitions for grapple states
    setStatePriority(0x16, 5, 1);           // state 0x16 = ? (e.g., GrabState::Start)
    enableState(0x31);                      // Enable state 0x31
    enableState(0x52);                      // Enable state 0x52 (PairedFinisher)
    setTransition(0x2E, s_globalFlag, 1);   // Transition from state 0x2E, condition from global, target state 1
    setState(0x2F);                         // Set state 0x2F
    enableState(0x19);                      // Enable state 0x19
    disableState(0x1A);                     // Disable state 0x1A
    disableState(0x54);                     // Disable state 0x54
    setState(0x53);                         // Set state 0x53

    // Register animation event names to IDs
    registerEvent("GrabEndPaired", 0x13);
    registerEvent("GrabKilledGrabbee", 0x30);
    registerEvent("Execution", 0x4E);       // Execution variation 1
    registerEvent("GrabPullup", 0x31);
    registerEvent("GrabDropToKnees", 0x2F);
    registerEvent("GrabBreak", 0x45);
    registerEvent("GrabRelease", 0x1E);
    registerEvent("PairedFinisher", 0x52);
    registerEvent("Execution", 0x53);       // Execution variation 2
    registerEvent("Execution", 0x54);       // Execution variation 3
    registerEvent("GrabMeleeAttackLeftA", 0x24);
    registerEvent("GrabMeleeAttackLeftA", 0x25);
    registerEvent("GrabMeleeAttackRightA", 0x26);
    registerEvent("GrabQuickAttackA", 0x1F);
    registerEvent("GrabQuickAttackB", 0x20);
    registerEvent("GrabQuickAttackC", 0x22);
    registerEvent("GrabChargeAttackLeftStart", 0x27);
    registerEvent("GrabChargeAttackRightStart", 0x2B);
    registerEvent("GrabMoveForwardsRight", 0x38);
    registerEvent("GrabMoveBackwardsRight", 0x34);
    registerEvent("GrabMoveBackwardsLeft", 0x36);
    registerEvent("GrabMoveForwardsLeft", 0x32);
    registerEvent("GrabSlam", 0x43);
    registerEvent("GrabThrowLeft", 0x3A);
    registerEvent("GrabThrowRight", 0x3B);
    registerEvent("GrabStrangle", 0x3E);
    registerEvent("GrabHoldThrow", 0x42);
}