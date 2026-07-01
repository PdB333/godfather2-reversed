// Xbox PDB: EARS_Modules_PlayerBlockSM_BuildStateMachine
// FUNC_NAME: PlayerBlockSM::initializeStateMachine
void PlayerBlockSM::initializeStateMachine(void)
{
  undefined4 stateMachineId;
  int isInitialized;
  
  stateMachineId = thunk_FUN_004dafd0("playerBlockSM");
  isInitialized = FUN_00621530(stateMachineId);
  if (isInitialized == 0) {
    stateMachineId = FUN_009c8f80();
    FUN_004ad9d0("playerBlockSM",stateMachineId);
    // Register state: BlockIdle
    FUN_004adae0("BlockIdle",0xffffffff);
    FUN_004ace70(0xa039288f,1,1,0,0x3f800000);
    FUN_004acf70(0x31);
    FUN_004acff0(0x32);
    FUN_004acc70("BlockDodgeLeft",0x14);
    FUN_004acc70("BlockDodgeRight",0x16);
    FUN_004acc70("BlockDodgeBack",0x18);
    FUN_004acc70("Terminate",0x1a);
    // Register state: BlockDodgeLeft
    FUN_004adae0("BlockDodgeLeft",0xffffffff);
    FUN_004ace70(0xc0ec76cf,1,1,0,0x3f800000);
    FUN_004acff0(0x32);
    FUN_004acc70("BlockDodgeRight",0x16);
    FUN_004acc70("BlockDodgeBack",0x18);
    FUN_004acc70("BlockIdle",0x15);
    FUN_004acc70("Terminate",0x1a);
    // Register state: BlockDodgeRight
    FUN_004adae0("BlockDodgeRight",0xffffffff);
    FUN_004ace70(0x28a564ea,1,1,0,0x3f800000);
    FUN_004acff0(0x32);
    FUN_004acc70("BlockDodgeLeft",0x14);
    FUN_004acc70("BlockDodgeBack",0x18);
    FUN_004acc70("BlockIdle",0x17);
    FUN_004acc70("Terminate",0x1a);
    // Register state: BlockDodgeBack
    FUN_004adae0("BlockDodgeBack",0xffffffff);
    FUN_004ace70(0xa039288f,1,1,0,0x3f800000);
    FUN_004acff0(0x32);
    FUN_004acc70("BlockDodgeLeft",0x14);
    FUN_004acc70("BlockDodgeRight",0x16);
    FUN_004acc70("BlockIdle",0x19);
    FUN_004acc70("Terminate",0x1a);
    // Register state: Terminate
    FUN_004adae0("Terminate",0xffffffff);
    FUN_004ad070(0x33);
    FUN_004acf70(2);
    FUN_004adc90(0x47fa72f,&LAB_007adb70,"PlayerBlockSM");
    FUN_004ada40();
  }
  return;
}