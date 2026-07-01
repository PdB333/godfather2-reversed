// Xbox PDB: EARS_Modules_CivilianVehicleStateMachine_BuildStateTable
// FUNC_NAME: CivilianVehicleStateMachine::registerStateMachine
void CivilianVehicleStateMachine::registerStateMachine(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = thunk_FUN_004dafd0("civilianVehicleMainTable");
  iVar2 = FUN_00621530(uVar1);
  if (iVar2 == 0) {
    uVar1 = FUN_009c8f80();
    FUN_004ad9d0("civilianVehicleMainTable",uVar1);
    FUN_004adae0("followGraph",0xffffffff);
    FUN_004acff0(10);
    FUN_004acc70(&DAT_00d63afc,0xc);
    FUN_004adae0(&DAT_00d63afc,0xffffffff);
    FUN_004acf70(0xb);
    FUN_004adc90(0x64ea38ff,&LAB_00873680,"CivilianVehicleStateMachine");
    FUN_004ada40();
  }
  return;
}