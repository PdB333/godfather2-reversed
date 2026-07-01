// Xbox PDB: EARS_Modules_NPCF2FStateMachine_BuildStateMachine
// FUNC_NAME: NPCF2FStateMachine::initializeStateTable
void NPCF2FStateMachine::initializeStateTable(void)
{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = thunk_FUN_004dafd0("NPCF2FStateTable");
  iVar1 = FUN_00621530(uVar2);
  if (iVar1 == 0) {
    uVar2 = FUN_009c8f80();
    FUN_004ad9d0("NPCF2FStateTable",uVar2);
    FUN_004adae0("F2F_Start",0xffffffff);
    FUN_004ad0f0(5,0x19,1);
    FUN_004acc70("F2F_Valid",0x17);
    FUN_004acc70("F2F_Inactive",4);
    FUN_004adae0("F2F_Inactive",0xffffffff);
    FUN_004acf70(0x29);
    FUN_004acd20("F2F_Valid",6,8,1);
    FUN_004acd20("F2F_Grab_Pain",6,1,1);
    FUN_004acc70("F2F_Terminate",0x17);
    FUN_004adae0("F2F_Valid",0xffffffff);
    FUN_004acf70(0x23);
    FUN_004acc70("F2F_Inactive",0x12);
    FUN_004acd20("F2F_Inactive",6,0x10,1);
    FUN_004acc70("F2F_Idle",4);
    FUN_004adae0("F2F_Idle",0xffffffff);
    FUN_004acf70(0x24);
    FUN_004acc70("F2F_NPCSpeaks",0x13);
    FUN_004acd20("F2F_Inactive",6,0x10,1);
    FUN_004acd20("F2F_Pain_Idle",6,1,1);
    FUN_004acc70("F2F_Inactive",0x15);
    FUN_004adae0("F2F_NPCSpeaks",0xffffffff);
    FUN_004acf70(0x26);
    FUN_004acc70("F2F_Idle",0x14);
    FUN_004acd20("F2F_Inactive",6,0x10,1);
    FUN_004acd20("F2F_Pain_Speaking",6,1,1);
    FUN_004acc70("F2F_Inactive",0x15);
    FUN_004adae0("F2F_Pain_Speaking",0xffffffff);
    FUN_004ad0f0(4,1,1);
    FUN_004acf70(0x16);
    FUN_004acf70(0x17);
    FUN_004acf10("painStateTable",1);
    FUN_004acc70("F2F_NPCSpeaks",0x18);
    FUN_004acd20("F2F_Inactive",6,0x10,1);
    FUN_004acc70("F2F_Pain_Speaking_End",1);
    FUN_004ad170(3,1,1);
    FUN_004acc70("F2F_Inactive",0x15);
    FUN_004adae0("F2F_Pain_Speaking_End",0xffffffff);
    FUN_004acf70(0x2b);
    FUN_004acc70("F2F_NPCSpeaks",4);
    FUN_004adae0("F2F_Pain_Idle",0xffffffff);
    FUN_004ad0f0(4,1,1);
    FUN_004acf70(0x16);
    FUN_004acf70(0x17);
    FUN_004acf10("painStateTable",1);
    FUN_004acc70("F2F_Idle",0x18);
    FUN_004acd20("F2F_Inactive",6,0x10,1);
    FUN_004acc70("F2F_Pain_Idle_End",1);
    FUN_004ad170(3,1,1);
    FUN_004acc70("F2F_Inactive",0x15);
    FUN_004adae0("F2F_Pain_Idle_End",0xffffffff);
    FUN_004acf70(0x2b);
    FUN_004acc70("F2F_Idle",4);
    FUN_004adae0("F2F_Grab_Pain",0xffffffff);
    FUN_004acf70(0x2a);
    FUN_004acc70("F2F_Terminate",0x19);
    FUN_004acc70("F2F_Inactive",4);
    FUN_004adae0("F2F_Terminate",0xffffffff);
    FUN_004acf70(0x27);
    FUN_004acf70(2);
    FUN_004adc90(0x187b7e2b,&LAB_00772f80,"NPCF2FStateMachine");
    FUN_004ada40();
  }
  return;
}