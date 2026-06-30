// Xbox PDB: EARS::Modules::NPCFollowSM::BuildStateMachine
// FUNC_NAME: NPCFollowComponent::buildFollowStateMachine
// Address: 0x00745f00
// This function constructs the hierarchical state machine for NPC follow behavior.
// It registers states, transitions, timers, and nested state machines for
// seeking, backing up, standing, chasing, and burst fire sub-behaviors.
void NPCFollowComponent::buildFollowStateMachine()
{
    // Possibly get a starting state ID or initial state handle
    uint32_t startHandle = stateMachineGetStartHandle(); // FUN_009c8f80

    // Set initial state name for the top-level state machine
    stateMachineSetInitialState("NPCFollowST", startHandle); // FUN_004ad9d0

    // --- Define states and transitions ---
    // State ID constants (inferred from function argument patterns)
    const int STATE_IDLE = 0;
    const int STATE_SEEK_SLOW = 0xf;    // 15
    const int STATE_SEEK_FAST = 0x10;   // 16
    const int STATE_BACKUP = 0x17;      // 23
    const int STATE_STAND_FOLLOW = 4;
    const int STATE_PATH_FAILURE = 0x11; // 17
    const int STATE_STRAFE_FAST = 0x16; // 22
    const int STATE_SEEK_TARGET = 0x12;  // 18
    const int STATE_CHASE = 0x1b;       // 27
    const int STATE_CHASE_SEEK = 0x1d;  // 29
    const int STATE_CHASE_SLOW = 0x13;  // 19
    const int STATE_BURST_FIRE = 0x1a;  // 26
    const int STATE_FOLLOW_PATH_FAIL = 0x20; // 32
    const int STATE_FOLLOW_WAIT = 0xc;  // 12
    const int STATE_FOLLOW_LOST = 0x1e; // 30
    const int STATE_FOLLOW_RECOVER = 0x22; // 34

    // First group: main follow states
    stateMachineAddState("standFollow", 0);      // STATE_IDLE
    stateMachineSetInitialState("standFollow", 1); // Flag or priority?
    stateMachineSetTimer(0x16); // 22
    stateMachineSetTimer(0x1e); // 30
    stateMachineSetTimer(0xc);  // 12
    stateMachineSetTimer(0x1b); // 27
    stateMachineSetTimer(0x1d); // 29
    stateMachineSetTimer(0x13); // 19

    stateMachineSetExitAction(0x17); // 23 (backup)
    stateMachinePushChildStateMachine("seekTargetTable", 1);

    stateMachineAddState(globalString_kInCover, 1); // DAT_00d63afc -> "inCover"? 
    stateMachineAddState(globalString_kInCover, 10); // 10
    stateMachineAddState(globalString_kInCover, 0x12); // 18
    stateMachineAddState("seekSlow", 0xf);
    stateMachineAddState("seekFast", 0x10);
    stateMachineAddState("backUp", 0x17);

    stateMachineSetStateTimer(0x1c); // 28
    stateMachineSetStateTimer(0x21); // 33

    stateMachineSetInitialState("seekFast", 2);
    stateMachineSetTimer(0x12); // 18
    stateMachineSetExitAction(0x19); // 25
    stateMachineSetExitAction(0x14); // 20
    stateMachinePushChildStateMachine("NPCChaseST", 1);

    stateMachineAddState(globalString_kInCover, 10);
    stateMachineAddState(globalString_kInCover, 0x12);
    stateMachineAddState("standFollow", 0xe); // 14
    stateMachineAddState("seekSlow", 0xd);   // 13
    stateMachineAddTransition("pathFailure", 6, 0x20, 1); // from id=6, to id=32, condition=1
    stateMachineAddState("pathFailure", 0x11);
    stateMachineAddState("strafeFast", 0x16);
    stateMachineAddState("standFollow", 1);

    stateMachineSetStateTimer(0x1a); // 26
    stateMachineSetInitialState("strafeFast", 3);
    stateMachineSetTimer(0x12);
    stateMachineSetExitAction(0x19);
    stateMachineSetExitAction(0x14);
    stateMachineSetExitAction(0x22); // 34
    stateMachinePushChildStateMachine("NPCChaseST", 1);
    stateMachinePushChildStateMachine("ContinualBurstFireST", 1);

    stateMachineAddState(globalString_kInCover, 10);
    stateMachineAddState(globalString_kInCover, 0x12);
    stateMachineAddState("standFollow", 0xe);
    stateMachineAddState("seekFast", 0x15); // 21
    stateMachineAddTransition("pathFailure", 6, 0x20, 1);
    stateMachineAddState("pathFailure", 0x11);
    stateMachineAddState("standFollow", 0x18); // 24

    stateMachineSetStateTimer(0x1a);
    stateMachineSetInitialState("seekSlow", 4);
    stateMachineSetTimer(0x15);
    stateMachineSetExitAction(0x19);
    stateMachinePushChildStateMachine("NPCChaseST", 1);
    stateMachineSetExitAction(0x14);

    stateMachineAddState(globalString_kInCover, 10);
    stateMachineAddState(globalString_kInCover, 0x12);
    stateMachineAddState("standFollow", 0xe);
    stateMachineAddState("seekFast", 0x10);
    stateMachineAddTransition("pathFailure", 6, 0x20, 1);
    stateMachineAddState("pathFailure", 0x11);
    stateMachineAddState("standFollow", 1);

    stateMachineSetStateTimer(0x1a);
    stateMachineSetInitialState("backUp", 5);
    stateMachinePushChildStateMachine("NPCBackupST", 1);

    stateMachineAddState(globalString_kInCover, 10);
    stateMachineAddState(globalString_kInCover, 0x12);
    stateMachineAddState("seekSlow", 0xf);
    stateMachineAddState("seekFast", 0x10);
    stateMachineAddState("standFollow", 1);

    stateMachineSetInitialState("pathFailure", 6);
    stateMachineSetTimer(0x18); // 24
    stateMachineAddTransition(6, 0x20, 1);
    stateMachineSetTimer(0xc);
    stateMachineSetTimer(0x1e);
    stateMachineSetExitAction(0x1f); // 31
    stateMachineSetExitAction(0x17);
    stateMachinePushChildStateMachine("seekTargetTable", 1);

    stateMachineAddState(globalString_kInCover, 10);
    stateMachineAddState(globalString_kInCover, 0x13);
    stateMachineAddState(globalString_kFollowIdle, 0x14); // DAT_00d63420 -> "followIdle"? 

    stateMachineSetInitialState(globalString_kInCover, 0xffffffff); // -1
    stateMachineSetTimer(2);

    // Register the complete state machine with a unique ID and entry function
    stateMachineRegister(0x8e2deeec, &NPCFollowSM_entry, "NPCFollowSM"); // FUN_004adc90

    stateMachineFinalize(); // FUN_004ada40
}