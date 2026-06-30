// FUNC_NAME: PlayerActionableTargetSM::handleActionableEvent
void __thiscall PlayerActionableTargetSM::handleActionableEvent(int this, int *param_2)
{
  char cVar1;
  int iVar2;
  int *piVar3;
  
  FUN_0045e670(param_2); // likely some event processing or validation
  if (DAT_012069c4 == *param_2) { // check event type against a known constant (e.g., kEvent_SomeAction)
    (**(code **)(*(int *)(this + -0x3c) + 0x208))(DAT_012067e8); // call a method on the parent state machine (offset 0x208)
    return;
  }
  if (((DAT_0120e93c == *param_2) && // check for another event type (e.g., kEvent_PlayerInput)
      ((*(int *)(this + 0x294) == 0 || (*(int *)(this + 0x294) == 0x48)))) && // check some state flags (0x48 might be a specific state ID)
     ((*(int *)(this + 0x284) != 0 || // check if any of the four action slots are occupied
      (((*(int *)(this + 0x288) != 0 || (*(int *)(this + 0x28c) != 0)) ||
       (*(int *)(this + 0x290) != 0)))))) {
    cVar1 = FUN_00445250(); // likely a check for player being in a valid state (e.g., not in cutscene)
    if (cVar1 != '\0') {
      iVar2 = FUN_00446130(this + 0x284, 0); // check if the first action slot (offset 0x284) has a valid action (index 0)
      if (iVar2 != 0) {
        piVar3 = (int *)FUN_005435d0(); // create or get some action object (e.g., a new ActionOptions)
        if (piVar3 != (int *)0x0) {
          (**(code **)(*(int *)(this + -0x3c) + 0x1a4))(piVar3); // call a method on the parent state machine (offset 0x1a4) to set the action
          (**(code **)(*piVar3 + 0x1c))(this + -0x3c); // call a method on the action object (vtable offset 0x1c) to execute it
        }
      }
    }
  }
  return;
}