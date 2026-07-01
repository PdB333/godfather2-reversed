// Xbox PDB: EARS_Modules_PlayerVehicleHijackSM_BuildStateMachine
// FUNC_NAME: PlayerVehicleHijackSM::registerStateTable
void PlayerVehicleHijackSM::registerStateTable(void)
{
  undefined4 stateTableName;
  int iVar2;
  
  stateTableName = thunk_FUN_004dafd0("playerVehicleHijackStateTable");
  iVar2 = FUN_00621530(stateTableName);
  if (iVar2 == 0) {
    stateTableName = FUN_009c8f80();
    FUN_004ad9d0("playerVehicleHijackStateTable",stateTableName);
    FUN_004adae0(&DAT_00d63420,0xffffffff);
    FUN_004acf70(0x31);
    FUN_004acc70("playAnim",3);
    FUN_004adae0("playAnim",0xffffffff);
    FUN_004acf10("playerStrafeMovementStateTable",1);
    FUN_004acf70(0x32);
    FUN_004acd20("terminate",9,0,1);
    FUN_004adae0("terminate",0xffffffff);
    FUN_004acf70(2);
    FUN_004adc90(0x1883c985,&LAB_007c5c60,"PlayerVehicleHijackSM");
    FUN_004ada40();
  }
  return;
}