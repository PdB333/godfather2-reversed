// Xbox PDB: EARS_Modules_PlayerActionableTargetSM_BuildStateMachine
// FUNC_NAME: PlayerActionableTargetSM::registerStates
void PlayerActionableTargetSM::registerStates(void)
{
  undefined4 uVar1;
  
  uVar1 = FUN_009c8f80(); // likely getStateMachineManager or similar
  FUN_004ad9d0("playerActionableTargetStateTable",uVar1); // registerStateTable
  FUN_004adae0("search",0xffffffff); // addState with no parent
  FUN_004acff0(0x31); // addTransition (0x31 = some input/event)
  FUN_004acff0(0x35); // addTransition (0x35 = another input/event)
  FUN_004acc70("disabled",0x13); // addState with parent state ID 0x13
  FUN_004adae0("disabled",0xffffffff); // addState with no parent (overwrite?)
  FUN_004acf70(0x32); // addTransition (0x32 = input/event)
  FUN_004acff0(0x33); // addTransition (0x33 = input/event)
  FUN_004acff0(0x34); // addTransition (0x34 = input/event)
  FUN_004acc70("search",0x14); // addState with parent state ID 0x14
  FUN_004adc90(0xc4bc3ce7,&LAB_007e3840,"PlayerActionableTargetSM"); // registerStateMachine with hash, entry function, name
  FUN_004ada40(); // finalizeStateMachine
  return;
}