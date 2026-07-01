// Xbox PDB: EARS_Modules_PlayerUseDisposableItemSM_BuildStateMachine
// FUNC_NAME: PlayerStateMachineManager::registerPlayerUseDisposableItemSM
void PlayerStateMachineManager::registerPlayerUseDisposableItemSM(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80(); // Get some global identifier (likely a hash or ID)
  FUN_004ad9d0("playerUseDisposableItemStateTable",uVar1); // Register state table name with ID
  FUN_004adae0(&DAT_00d63420,0xffffffff); // Set default state (0xFFFFFFFF = no state)
  FUN_004acf70(0x31); // Begin state definition for state 0x31 (49)
  FUN_004acc70("conceal",0x13); // Add transition "conceal" to state 0x13 (19)
  FUN_004acc70("pickup",4); // Add transition "pickup" to state 4
  FUN_004adae0("conceal",0xffffffff); // Set default transition for "conceal" to none
  FUN_004acf70(0x32); // Begin state definition for state 0x32 (50)
  FUN_004acf10("playerConcealItemStateTable",1); // Set substate machine with flag 1
  FUN_004acc70("pickup",1); // Add transition "pickup" to state 1
  FUN_004adae0("pickup",0xffffffff); // Set default transition for "pickup" to none
  FUN_004acf70(0x33); // Begin state definition for state 0x33 (51)
  FUN_004acc70(&DAT_00d64b74,0x14); // Add transition with string at DAT_00d64b74 to state 0x14 (20)
  FUN_004adae0(&DAT_00d64b74,0xffffffff); // Set default transition for that string to none
  FUN_004acc70("throwItem",0x16); // Add transition "throwItem" to state 0x16 (22)
  FUN_004acc70("terminate",0x15); // Add transition "terminate" to state 0x15 (21)
  FUN_004adae0("throwItem",0xffffffff); // Set default transition for "throwItem" to none
  FUN_004acf10("playerThrowItemStateTable",0); // Set substate machine with flag 0
  FUN_004acc70("terminate",1); // Add transition "terminate" to state 1
  FUN_004adae0("terminate",0xffffffff); // Set default transition for "terminate" to none
  FUN_004acf70(2); // Begin state definition for state 2
  FUN_004adc90(0x7001d9d3,&LAB_007df220,"PlayerUseDisposableItemSM"); // Register state machine with hash, function pointer, and name
  FUN_004ada40(); // Finalize registration
  return;
}