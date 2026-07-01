// Xbox PDB: EARS_Modules_PlayerPlantSM_BuildStateMachine
// FUNC_NAME: PlayerPlantStateTable::initStateTable
void PlayerPlantStateTable::initStateTable(void)

{
  undefined4 stateMachineId;
  
  // Create a new state machine ID for "playerPlantStateTable" by name
  stateMachineId = FUN_009c8f80();
  FUN_004ad9d0("playerPlantStateTable",stateMachineId);
  
  // Register global transitions for the entire state table
  FUN_004adae0(&DAT_00d63420,0xffffffff); // global transition - likely error/abort handler
  
  // Add states with their internal IDs
  FUN_004acf70(0x33); // state: decide/plant? (base)
  FUN_004acf70(0x35); // state something else
  
  // Add transition "decide" with priority 3
  FUN_004acc70("decide",3);
  FUN_004adae0("decide",0xffffffff); // global transition for "decide"
  
  // Add transitions for various actions
  FUN_004acc70("switch",0x13);
  FUN_004acc70("reveal",0x14);
  FUN_004acc70("GhostPlantWait",0x17);
  FUN_004acc70("plant",4);
  FUN_004adae0("GhostPlantWait",0xffffffff);
  FUN_004acc70("plant",0x18);
  FUN_004adae0("switch",0xffffffff);
  
  // Begin sub-table for switch item
  FUN_004acf10("playerSwitchItemStateTable",1);
  FUN_004acc70("decide",1);
  FUN_004adae0("reveal",0xffffffff);
  
  // Begin sub-table for reveal item
  FUN_004acf10("playerRevealItemStateTable",1);
  FUN_004acc70("decide",1);
  FUN_004adae0("plant",0xffffffff);
  
  // Additional states
  FUN_004acf70(0x31);
  FUN_004ad070(0x32);
  
  // Transition with auto-restore logic
  FUN_004acd80("checkAutoRestore",2,_DAT_00d5cf70,1);
  FUN_004adae0("checkAutoRestore",0xffffffff);
  FUN_004acc70("autoRestore",0x16);
  FUN_004acc70("checkAutoReveal",4);
  FUN_004adae0("autoRestore",0xffffffff);
  
  // Auto-reveal branch
  FUN_004acf70(0x34);
  FUN_004acc70("checkAutoReveal",3);
  FUN_004adae0("checkAutoReveal",0xffffffff);
  FUN_004acc70("autoReveal",0x15);
  FUN_004acc70("terminate",4);
  FUN_004adae0("autoReveal",0xffffffff);
  
  // Final sub-table for reveal item with terminate
  FUN_004acf10("playerRevealItemStateTable",1);
  FUN_004acc70("terminate",1);
  FUN_004adae0("terminate",0xffffffff);
  
  // End states
  FUN_004acf70(0x36);
  FUN_004acf70(2);
  
  // Register the state machine with ID and name, binding to a handler
  FUN_004adc90(0x9db097c4,&LAB_007c3220,"PlayerPlantSM");
  FUN_004ada40(); // Finalize registration
  
  return;
}