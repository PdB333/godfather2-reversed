// FUNC_NAME: PlayerSM::initializeStateMachine
void PlayerSM::initializeStateMachine(void *param_1)

{
  int stateMachine;
  
  stateMachine = FUN_009c8e50(0xf0);
  if (stateMachine == 0) {
    stateMachine = 0;
  }
  else {
    stateMachine = FUN_00982280(0);
  }
  *(undefined4 *)(stateMachine + 0xc) = 3; // +0x0C: initial state ID (e.g., standing)
  FUN_00981eb0(param_1);
  FUN_00982400(1);
  *(code **)(stateMachine + 0x14) = FUN_00982b30; // +0x14: state transition function pointer
  FUN_00982e10();
  return;
}