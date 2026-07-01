// FUNC_NAME: SomeClass::checkAndProcessState
void SomeClass::checkAndProcessState(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  // Check if the state at offset +0x4 is not equal to 7
  // +0x04: current state identifier
  if (*(int *)(param_1 + 4) != 7) {
    // If state is not 7, call processing functions
    // FUN_008c80d0 likely handles param_3 (e.g., a data buffer or event)
    FUN_008c80d0(param_3);
    // FUN_008c8a20 likely handles param_2 and param_4 (e.g., input/output parameters)
    FUN_008c8a20(param_2, param_4);
  }
  return;
}