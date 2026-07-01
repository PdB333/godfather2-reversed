// FUNC_NAME: StreamManager::advanceReadPosition
void StreamManager::advanceReadPosition(int *param_1)

{
  // Dereference param_1 to get the stream object pointer, add 0xC offset (likely current read pointer or buffer)
  FUN_00859680(*param_1 + 0xc);
  // Call internal function to finalize the position update
  FUN_00859730(param_1);
  return;
}