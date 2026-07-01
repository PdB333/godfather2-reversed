// Xbox PDB: EARS_Modules_ShootSM_BuildShootStateTable
// FUNC_NAME: ShootStateMachine::buildShootST
void ShootStateMachine::buildShootST(void)
{
  uint32_t stateId;
  
  stateId = FUN_009c8f80(); // likely getNextStateId() or similar
  FUN_004ad9d0("ShootST",stateId); // registerState("ShootST", stateId)
  FUN_004adae0(&DAT_00d63420,0xffffffff); // setTransition(globalState, -1)
  FUN_004acc70("burst",0x15); // addState("burst", 0x15) - burst fire state
  FUN_004acc70("delayedStart",4); // addState("delayedStart", 4) - delayed start state
  FUN_004adae0("delayedStart",0xffffffff); // setTransition("delayedStart", -1)
  FUN_004acf70(0x23); // setStateFlags(0x23) - likely some state flags
  FUN_004acf10("seekTargetTable",1); // addTransition("seekTargetTable", 1) - transition to seek target table
  FUN_004acc70("burst",0x15); // addState("burst", 0x15) - burst fire state
  FUN_004adae0("burst",0xffffffff); // setTransition("burst", -1)
  FUN_004acf10("BurstFireST",1); // addTransition("BurstFireST", 1) - transition to burst fire state machine
  FUN_004acc70("testDone",1); // addState("testDone", 1) - test done state
  FUN_004adae0("testDone",0xffffffff); // setTransition("testDone", -1)
  FUN_004acf70(0x24); // setStateFlags(0x24) - likely some state flags
  FUN_004acc70(&DAT_00d63afc,0x14); // addState("waitForBurst", 0x14) - wait for burst state
  FUN_004acc70("waitForBurst",0x12); // addState("waitForBurst", 0x12) - wait for burst state
  FUN_004acc70(&DAT_00d63afc,4); // addState("waitForBurst", 4) - wait for burst state
  FUN_004adae0("waitForBurst",0xffffffff); // setTransition("waitForBurst", -1)
  FUN_004acf70(0x23); // setStateFlags(0x23) - likely some state flags
  FUN_004acf10("seekTargetTable",1); // addTransition("seekTargetTable", 1) - transition to seek target table
  FUN_004acc70("burst",0x13); // addState("burst", 0x13) - burst fire state
  FUN_004adae0(&DAT_00d63afc,0xffffffff); // setTransition("waitForBurst", -1)
  FUN_004acf70(2); // setStateFlags(2) - likely some state flags
  FUN_004adc90(0x44be8ae2,&LAB_0076d120,"ShootSM"); // registerStateMachine(0x44be8ae2, &LAB_0076d120, "ShootSM")
  FUN_004ada40(); // finalizeStateMachine()
  return;
}