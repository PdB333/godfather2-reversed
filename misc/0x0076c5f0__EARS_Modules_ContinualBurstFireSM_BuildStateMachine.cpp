// Xbox PDB: EARS_Modules_ContinualBurstFireSM_BuildStateMachine
// FUNC_NAME: ContinualBurstFireSM::setupStateMachine
void ContinualBurstFireSM::setupStateMachine(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80();
  FUN_004ad9d0("ContinualBurstFireST",uVar1);
  FUN_004adae0(&DAT_00d63420,0xffffffff);
  FUN_004acc70("terminate",0x12);
  FUN_004acc70("noAnimShootUpdate",4);
  FUN_004adae0("noAnimShootUpdate",0xffffffff);
  FUN_004acff0(0x23);
  FUN_004acc70("terminate",0x12);
  FUN_004adae0("terminate",0xffffffff);
  FUN_004acf70(2);
  FUN_004adc90(0x5ea8c0e7,&LAB_0076c1a0,"ContinualBurstFireSM");
  FUN_004ada40();
  return;
}