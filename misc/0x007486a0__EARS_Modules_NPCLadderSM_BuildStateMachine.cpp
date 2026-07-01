// Xbox PDB: EARS::Modules::NPCLadderSM::BuildStateMachine
// FUNC_NAME: NPCLadderStateMachine::buildFSM

void NPCLadderStateMachine::buildFSM(void)
{
    int smId;

    // Get a new state machine identifier (likely from the FSM manager)
    smId = FUN_009c8f80();

    // Register the state machine with name "NPCLadderST"
    FUN_004ad9d0("NPCLadderST", smId);

    // Set initial state to global data pointer (probably a default idle state) with offset 0
    FUN_004adae0(&DAT_00d63420, 0);

    // Set state type for state index 0x12 (18)
    FUN_004acf70(0x12);

    // Define actions/events for various states
    // State "ladderClimbFailed" with action ID 0xd (13)
    FUN_004acc70("ladderClimbFailed", 0xd);
    // State "approachLadder" with action ID 10
    FUN_004acc70("approachLadder", 10);
    // State "enterLadder" with action ID 4
    FUN_004acc70("enterLadder", 4);

    // Set transition from "approachLadder" to state index 1 (probably the next state)
    FUN_004adae0("approachLadder", 1);

    // Set timeout for state 5 with mask 0x20 and flag 1
    FUN_004ad0f0(5, 0x20, 1);

    // Associate sub-state machine "SeekToPositionST" with state index 1
    FUN_004acf10("SeekToPositionST", 1);

    // Add conditional transition from "approachLadderFailed" to state 6 with mask 0x20 and flag 1
    FUN_004acd20("approachLadderFailed", 6, 0x20, 1);

    // Define state "ladderClimbFailed" (again) with action ID 0xd
    FUN_004acc70("ladderClimbFailed", 0xd);
    // State "enterLadder" with action ID 1
    FUN_004acc70("enterLadder", 1);

    // Set transition for state 4 with mask 0x20 and flag 1
    FUN_004ad170(4, 0x20, 1);

    // Set transition from "approachLadderFailed" to state index 2
    FUN_004adae0("approachLadderFailed", 2);

    // Set state type for index 0x17 (23)
    FUN_004acf70(0x17);

    // Define state "terminate" with action ID 4
    FUN_004acc70("terminate", 4);

    // Set transition from "enterLadder" to state index 3
    FUN_004adae0("enterLadder", 3);

    // Define states for climbing phase
    FUN_004acc70("ladderClimbFailed", 0xd);
    FUN_004acc70("ladderClimb", 0xc);
    FUN_004acc70("ladderClimbWait", 4);

    // Set transition from "ladderClimbWait" to state index 4
    FUN_004adae0("ladderClimbWait", 4);

    // Set state type for index 0x13 (19)
    FUN_004acf70(0x13);

    // Define states for climbing continuation
    FUN_004acc70("ladderClimbFailed", 0xd);
    FUN_004acc70("ladderClimb", 0xc);
    FUN_004acc70("ladderClimbFailed", 0x10);

    // Set transition from "ladderClimb" to state index 5
    FUN_004adae0("ladderClimb", 5);

    // Set state type for index 0x14 (20)
    FUN_004acf70(0x14);

    // Define sub-state machine "LadderClimbStateTable" with index 0
    FUN_004acf10("LadderClimbStateTable", 0);

    // Define states for end of climb
    FUN_004acc70("ladderDeath", 0xf);
    FUN_004acc70("completedLadderClimb", 1);

    // Set state machine property for index 0x15 (21)
    FUN_004ad070(0x15);

    // Set transition from "ladderDeath" to state index 6
    FUN_004adae0("ladderDeath", 6);

    // Set state type for index 0x16 (22)
    FUN_004acf70(0x16);

    // Define states for completion handling
    FUN_004acc70("terminate", 4);
    FUN_004adae0("completedLadderClimb", 7);
    FUN_004acc70("ladderClimbFailed", 0xe);
    FUN_004acc70("gotoFinalPos", 0xb);
    FUN_004acc70("terminate", 4);
    FUN_004adae0("gotoFinalPos", 8);
    FUN_004ad0f0(5, 0x20, 1);
    FUN_004acf10("SeekToPositionST", 1);
    FUN_004acd20("seekToFinalPosFailed", 6, 0x20, 1);
    FUN_004acc70("terminate", 1);
    FUN_004ad170(4, 0x20, 1);
    FUN_004adae0("seekToFinalPosFailed", 9);
    FUN_004acf70(0x17);
    FUN_004acc70("terminate", 4);
    FUN_004adae0("ladderClimbFailed", 10);
    FUN_004acf70(0x17);
    FUN_004acc70("terminate", 4);
    FUN_004adae0("terminate", 0xffffffff);
    FUN_004acf70(2);

    // Register the state machine globally with the data block at LAB_00748670, named "NPCLadderSM"
    FUN_004adc90(0x5be975d, &LAB_00748670, "NPCLadderSM");

    // Finalize or cleanup state machine building
    FUN_004ada40();
    return;
}