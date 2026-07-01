// Xbox PDB: EARS_Modules_VehicleReverseStateMachine_BuildStateTable
// FUNC_NAME: VehicleReverseStateMachine::registerReverseTable
void VehicleReverseStateMachine::registerReverseTable(void)

{
  undefined4 tableName;
  int iVar2;
  
  tableName = thunk_FUN_004dafd0("vehicleReverseTable");
  iVar2 = FUN_00621530(tableName);
  if (iVar2 == 0) {
    tableName = FUN_009c8f80();
    FUN_004ad9d0("vehicleReverseTable",tableName);
    FUN_004adae0("reverse",0xffffffff);
    FUN_004acff0(10);
    FUN_004acc70(&DAT_00d63afc,0xb);
    FUN_004acd80(&DAT_00d63afc,2,_DAT_00d75d50,1);
    FUN_004adae0(&DAT_00d63afc,0xffffffff);
    FUN_004acf70(2);
    FUN_004adc90(0x72703570,&LAB_0086b3b0,"VehicleReverseStateMachine");
    FUN_004ada40();
  }
  return;
}