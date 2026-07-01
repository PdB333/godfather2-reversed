// FUNC_NAME: PlayerSM::canPerformAction
undefined4 __thiscall PlayerSM::canPerformAction(int this, undefined4 param_2, undefined4 param_3, int actionId, undefined4 param_5)
{
  undefined4 result;
  int iVar2;
  int *piVar3;
  float10 extraout_ST0;
  float local_c;
  float local_8;
  float local_4;
  
  if (actionId == 0x12) { // ACTION_GRAPPLE
    if ((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) { // Check current state
      FUN_0076a540(&local_c); // Get player position
      iVar2 = FUN_00471610(); // Get some object (target?)
      local_c = *(float *)(iVar2 + 0x30) - local_c; // Calculate distance vector
      local_8 = *(float *)(iVar2 + 0x34) - local_8;
      local_4 = *(float *)(iVar2 + 0x38) - local_4;
      if (local_4 * local_4 + local_8 * local_8 + local_c * local_c < DAT_00e51bcc * DAT_00e51bcc) { // Check distance squared
        return 1; // Can perform grapple
      }
    }
  }
  else {
    if (actionId == 0x13) { // ACTION_TAKEDOWN
      if (((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) &&
         (*(char *)(this + 0x84) != '\0')) { // Check state and some flag
        if (*(int *)(this + 0x70) == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(this + 0x70) + -0x48; // Get state object pointer
        }
        if ((*(uint *)(iVar2 + 0xa18) >> 0x19 & 1) == 0) { // Check some state flag
          if (*(int *)(this + 0x70) == 0) {
            piVar3 = (int *)0x0;
          }
          else {
            piVar3 = (int *)(*(int *)(this + 0x70) + -0x48);
          }
          (**(code **)(*piVar3 + 0x4c))(&local_c); // Get some value from state
          FUN_0046cb10(&stack0xfffffff0); // Compare with threshold
          if (extraout_ST0 <= (float10)_DAT_00e51bd0) {
            return 0; // Cannot perform takedown
          }
        }
      }
      return 1; // Can perform takedown
    }
    if (actionId != 0x14) { // ACTION_THROW
      result = FUN_0073e300(param_2, param_3, actionId, param_5); // Delegate to base class
      return result;
    }
    if (DAT_00e445fc < *(float *)(this + 0x88)) { // Check some timer/cooldown
      return 1; // Can throw
    }
  }
  return 0; // Cannot perform action
}