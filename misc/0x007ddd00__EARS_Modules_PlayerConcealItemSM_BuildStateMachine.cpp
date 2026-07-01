// Xbox PDB: EARS_Modules_PlayerConcealItemSM_BuildStateMachine
// FUNC_NAME: PlayerConcealItemSM::initializeStateTable
void PlayerConcealItemSM::initializeStateTable(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80();  // Call to get some table resource
  FUN_004ad9d0("playerConcealItemStateTable",uVar1); // Register state table
  FUN_004adae0("conceal",0xffffffff); // Add state named "conceal" with ID -1
  FUN_004acf70(0x31); // Set state duration? 0x31 = 49 frames
  FUN_004acc70(&DAT_00d63ba4,0x13); // Set animation clip (offset +0x13)
  FUN_004adae0(&DAT_00d63ba4,0xffffffff); // Add another state
  FUN_004acf70(2); // Set state duration to 2 frames
  FUN_004adc90(0xfcc7f42f,&LAB_007ddc90,"PlayerConcealItemSM"); // Register transition with hash
  FUN_004ada40(); // Finalize state table
  return;
}