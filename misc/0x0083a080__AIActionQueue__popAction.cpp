// FUNC_NAME: AIActionQueue::popAction
void __fastcall AIActionQueue::popAction(int this)
{
  char result;
  int actionData;

  actionData = this;
  result = FUN_00839ef0((undefined4 *)(this + 0x4c), &actionData);
  if (result != 0) {
    *(undefined4 *)(this + 0x58) = 0;
    *(undefined4 *)(this + 0x54) = 0;
    *(undefined4 *)(this + 0x50) = 0;
    *(undefined4 *)(this + 0x4c) = 0;
    *(int *)(this + 0x1c) = actionData;  // Store popped action data
    FUN_00839310();  // Notify observers or update state
    return;
  }
  return;
}