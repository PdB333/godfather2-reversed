// Xbox PDB: EARS_Modules_GrabReactStateMachine_BuildGrappleStateTable
// FUNC_NAME: GrabReactStateMachine::registerStates
void GrabReactStateMachine::registerStates(void)
{
  undefined4 stateTable;
  int iVar2;
  
  stateTable = thunk_FUN_004dafd0("grabReactStateTable");
  iVar2 = FUN_00621530(stateTable);
  if (iVar2 == 0) {
    stateTable = FUN_009c8f80();
    FUN_004ad9d0("grabReactStateTable",stateTable);
    FUN_004adae0("pairedStart",0xffffffff);
    FUN_004acf70(0xc);
    FUN_004ad0f0(5,0x1c,1);
    FUN_004acc70("pairedInactive",10);
    FUN_004acc70("paired",4);
    FUN_004adae0("pairedInactive",0xffffffff);
    FUN_004acf70(0xe);
    FUN_004acf70(0x10);
    FUN_004acf70(0xf);
    FUN_004acf70(0x11);
    FUN_004acd20("terminate",6,0x10,1);
    FUN_004acd20("pairedF2F",6,4,1);
    FUN_004acc70("terminate",0xb);
    FUN_004adae0("paired",0xffffffff);
    FUN_004acf70(10);
    FUN_004acff0(0xb);
    FUN_004acd20("paired",6,4,1);
    FUN_004acd20("pairedF2F",6,8,1);
    FUN_004acc70("terminate",10);
    FUN_004adae0("pairedF2F",0xffffffff);
    FUN_004acf70(0xd);
    FUN_004acff0(0xb);
    FUN_004acd20("pairedF2F",6,4,1);
    FUN_004acd20("paired",6,0x10,1);
    FUN_004acc70("pairedInactive",10);
    FUN_004acc70("paired",0xb);
    FUN_004adae0("terminate",0xffffffff);
    FUN_004acf70(0xf);
    FUN_004acf70(0x11);
    FUN_004acf70(2);
    FUN_004adc90(0xf9dca109,&LAB_0080c990,"GrabReactStateMachine");
    FUN_004ada40();
  }
  return;
}