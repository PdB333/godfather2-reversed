// Xbox PDB: EARS_Modules_PlayerUseItemSM_BuildStateMachine
// FUNC_NAME: PlayerUseItemStateTable::initializeStateTable
void PlayerUseItemStateTable::initializeStateTable(void)

{
  undefined4 stateTableId;
  int iVar2;
  
  stateTableId = thunk_FUN_004dafd0("playerUseItemStateTable");
  iVar2 = FUN_00621530(stateTableId);
  if (iVar2 == 0) {
    stateTableId = FUN_009c8f80();
    FUN_004ad9d0("playerUseItemStateTable",stateTableId);
    // Initialize state transitions for use item state machine
    FUN_004adae0("useItemDelay",0xffffffff);  // Transition with infinite timeout
    FUN_004acc70("useItem",0x15);             // Set state for use item (21)
    FUN_004adae0("useItem",0xffffffff);       // Another infinite timeout transition
    FUN_004acf70(0x31);                       // Set entry action (49)
    FUN_004acff0(0x32);                       // Set exit action (50)
    FUN_004acc70(&DAT_00d63ba4,0x13);         // Set state (19)
    FUN_004acc70("useItem",0x14);             // Set state for use item (20)
    FUN_004adae0(&DAT_00d63ba4,0xffffffff);   // Transition with infinite timeout
    FUN_004acf70(2);                          // Set entry action (2)
    FUN_004adc90(0xa395ad0c,&LAB_007dff40,"PlayerUseItemSM"); // Register state machine callback
    FUN_004ada40();                           // Finalize state table initialization
  }
  return;
}