// FUNC_NAME: ControllerManager::processInputEvent
void __fastcall ControllerManager::processInputEvent(int thisPtr)
{
  if (*(int *)(thisPtr + 0x30) != 0) {
    // Call the input processor function pointer stored in the action mapping
    (**(code **)(*(int *)(*(int *)(thisPtr + 0x30) + 4) + 0x10))();
    return;
  }
  return;
}