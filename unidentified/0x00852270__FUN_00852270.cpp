// FUNC_NAME: SomeClass::processPendingAction
void __thiscall processPendingAction(int this, int param_2)
{
  int *piVar1;
  char cVar2;
  
  // Check if current action is null (0x18 = currentAction pointer)
  // and param_2 has a valid action pointer (param_2 + 4 = actionList)
  // and the first action's ID matches the expected ID (0x14 = expectedActionId)
  if (((*(int *)(this + 0x18) == 0) && (*(int **)(param_2 + 4) != (int *)0x0)) &&
     (**(int **)(param_2 + 4) == *(int *)(this + 0x14))) {
    // Decrement pending action count (0x1c = pendingActionCount)
    piVar1 = (int *)(this + 0x1c);
    *piVar1 = *piVar1 + -1;
    // If pending count reaches zero and validation succeeds (0x4 = validationState)
    if ((*piVar1 == 0) && (cVar2 = FUN_00420950(this + 4), cVar2 != '\0')) {
      // Set current action to the provided action (0x18 = currentAction)
      *(int *)(this + 0x18) = param_2;
    }
  }
  return;
}