// FUNC_NAME: ActionBase::initFromParams
void __thiscall ActionBase::initFromParams(int param_2, int param_3, int param_4)
{
  // Offset 0x30: duration or delay value
  *(int *)(this + 0x30) = param_2;
  // Offset 0x48: target entity ID
  *(int *)(this + 0x48) = param_3;
  // Offset 0x4c: some flag or parameter
  *(int *)(this + 0x4c) = param_4;
  // Offset 0x40: clear previous state/flag
  *(int *)(this + 0x40) = 0;
  // Release previous object stored at +0x3c (e.g., a linked action or callback)
  FUN_009c8f10(*(int *)(this + 0x3c));
  // Clear the pointer
  *(int *)(this + 0x3c) = 0;
  // Offset 0x44: clear another pointer/counter
  *(int *)(this + 0x44) = 0;
  // Register this action with the engine (likely into an update list)
  FUN_004c3c70(1);
  // Offset 0x1c: set "active" or "valid" flag to 1
  *(int *)(this + 0x1c) = 1;
}