// Xbox PDB: EARS_Modules_VehicleIdleSM_BuildStateTable
// FUNC_NAME: FSMMachine::setupVehicleIdleSM
void FSMMachine::setupVehicleIdleSM(void)
{
  undefined4 result;
  
  result = FUN_009c8f80(); // probably createStateMachine or getStateMachineId
  FUN_004ad9d0("VehicleIdleST",result); // registerStateName
  FUN_004adae0(&DAT_00d64b74,0xffffffff); // setTransition(-1) or clearTransitions
  FUN_004acf70(10); // pushStateParameter or setStateTimeout
  FUN_004acff0(10); // popStateParameter or setStateTimer
  FUN_004adc90(0x3e3b465a,&LAB_00882f80,"VehicleIdleSM"); // registerStateMachine(name, tickFunc)
  FUN_004ada40(); // finalizeStateMachine / initializeSM
  return;
}