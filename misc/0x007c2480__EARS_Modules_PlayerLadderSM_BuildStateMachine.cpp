// Xbox PDB: EARS_Modules_PlayerLadderSM_BuildStateMachine
// FUNC_NAME: PlayerLadderSM::registerStates
void PlayerLadderSM::registerStates(void)
{
  // Get a state machine factory or manager instance
  undefined4 factory = FUN_009c8f80();  // likely getStateMachineFactory()
  
  // Register the player ladder state table
  FUN_004ad9d0("playerLadderStateTable", factory);  // registerStateTable
  
  // Add ladderClimb as a default state (0xffffffff = no parent)
  FUN_004adae0("ladderClimb", 0xffffffff);  // addState
  
  // Register the LadderClimbStateTable as a substate machine
  FUN_004acf10("LadderClimbStateTable", 1);  // registerSubStateMachine
  
  // Add terminate transitions for various states (0x13, 0x14, 1)
  FUN_004acc70("terminate", 0x13);  // addTransition
  FUN_004acc70("terminate", 0x14);
  FUN_004acc70("terminate", 1);
  
  // Set terminate as a default transition (0xffffffff = no parent)
  FUN_004adae0("terminate", 0xffffffff);  // addState
  
  // Set the number of states or finalize registration
  FUN_004acf70(2);  // setStateCount or finalize
  
  // Register a state machine with a hash ID and label
  FUN_004adc90(0x8705779d, &LAB_007c2450, "PlayerLadderSM");  // registerStateMachine
  
  // Cleanup or pop context
  FUN_004ada40();  // popStateMachineContext
  return;
}