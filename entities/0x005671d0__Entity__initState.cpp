// FUNC_NAME: Entity::initState
void __thiscall Entity::initState(int param_1, int param_2)
{
  // Set state type to 9 (e.g., kStateType_Active or similar)
  *(int *)(param_1 + 0x10) = 9;
  // Set sub-state to 2 (e.g., kSubState_Idle or kSubState_Moving)
  *(char *)(param_1 + 0x14) = 2;
  // Store external parameter (e.g., controller index, target ID, or resource handle)
  *(int *)(param_1 + 0x18) = param_2;
  return;
}