// Xbox PDB: EARS_Modules_VehicleScriptedSequenceSM_BuildStateTable
// FUNC_NAME: VehicleScriptedSequenceTable::initialize
void VehicleScriptedSequenceTable::initialize(void)
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = thunk_FUN_004dafd0("vehicleScriptedSequenceTable");
  iVar1 = FUN_00621530(uVar1);
  if (iVar1 == 0) {
    FUN_00871480();
    uVar2 = FUN_009c8f80();
    FUN_004ad9d0("vehicleScriptedSequenceTable",uVar2);
    FUN_004adae0(&DAT_00d64b74,0xffffffff);
    FUN_004acf70(10);
    FUN_004acff0(8);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70("gotoSS",0xb);
    FUN_004adae0("gotoSS",0xffffffff);
    FUN_004acf70(0xb);
    FUN_004acff0(8);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70("pathToPos",0xf);
    FUN_004acc70("waitAtSS",0xe);
    FUN_004acc70("faceOrient",0x10);
    FUN_004acc70(&DAT_00d63afc,0x14);
    FUN_004adae0("pathToPos",0xffffffff);
    FUN_004acf10("vehicleFollowPathTable",0);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70("waitAtSS",0xc);
    FUN_004acc70("faceOrient",1);
    FUN_004adae0("faceOrient",0xffffffff);
    FUN_004acf70(0xf);
    FUN_004acff0(0x10);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70("waitAtSS",0xd);
    FUN_004adae0("waitAtSS",0xffffffff);
    FUN_004acf70(0xd);
    FUN_004acf70(0xe);
    FUN_004acff0(0xe);
    FUN_004acff0(8);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70("action",0x13);
    FUN_004adae0("action",0xffffffff);
    FUN_004acf70(0xc);
    FUN_004acff0(8);
    FUN_004acc70(&DAT_00d63afc,0x15);
    FUN_004acc70(&DAT_00d63afc,0x11);
    FUN_004acc70("action",0x12);
    FUN_004adae0(&DAT_00d63afc,0xffffffff);
    FUN_004acf70(0x11);
    FUN_004adc90(0xa567a9e,&LAB_008728d0,"VehicleScriptedSequenceSM");
    FUN_004ada40();
  }
  return;
}