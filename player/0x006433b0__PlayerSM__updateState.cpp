// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(undefined4 param_1)
{
  undefined4 *in_EAX;
  
  FUN_00642b00(); // likely updateStateMachine or processTransitions
  switch(*in_EAX) {
  case 1: // e.g., kStateIdle
  case 3: // e.g., kStateWalking
    FUN_00642880(param_1); // handleStateIdleOrWalking
    return;
  case 2: // e.g., kStateRunning
    FUN_006424b0(); // handleRunningSpecific
    FUN_00642880(param_1); // handleStateIdleOrWalking
    return;
  default: // unknown state
    FUN_006432a0(1); // setState(1) - transition to idle
    FUN_00642880(param_1); // handleStateIdleOrWalking
    return;
  case 9: // e.g., kStateDead
    FUN_00642880(param_1); // handleStateDead
    return;
  }
}