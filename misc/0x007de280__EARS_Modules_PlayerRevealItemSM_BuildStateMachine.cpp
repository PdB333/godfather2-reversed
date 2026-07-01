// Xbox PDB: EARS_Modules_PlayerRevealItemSM_BuildStateMachine
// FUNC_NAME: PlayerRevealItemStateTable::registerStateTable
void PlayerRevealItemStateTable::registerStateTable(void)
{
  undefined4 stateTableName;
  int iVar2;
  
  // Look up the state table by name
  stateTableName = thunk_FUN_004dafd0("playerRevealItemStateTable");
  iVar2 = FUN_00621530(stateTableName);
  if (iVar2 == 0) {
    // State table doesn't exist yet, create it
    stateTableName = FUN_009c8f80();
    FUN_004ad9d0("playerRevealItemStateTable",stateTableName);
    
    // Register states
    FUN_004adae0("reveal",0xffffffff);  // State: reveal, no timeout
    FUN_004acf70(0x31);                 // Set state flags (0x31 = 49)
    
    // Register another state
    FUN_004acc70(&DAT_00d63ba4,0x13);   // State name from data, 0x13 = 19
    FUN_004adae0(&DAT_00d63ba4,0xffffffff); // No timeout
    FUN_004acf70(2);                    // Set state flags (2)
    
    // Register state machine transitions
    FUN_004adc90(0xfa3cd243,&LAB_007de210,"PlayerRevealItemSM");
    FUN_004ada40();                     // Finalize state table registration
  }
  return;
}