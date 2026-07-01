// FUNC_NAME: PlayerF2FSM::handleF2FStateTransition
void __thiscall PlayerF2FSM::handleF2FStateTransition(int this, uint param_2)
{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  // Check if state at offset +0x30 is 1 or 2 (valid F2F states)
  if (*(int *)(param_2 + 0x30) - 1U < 2) {
    // Check if entity pointer at +0xc is null or has specific type (0x48 = F2F entity?)
    if ((*(int *)(param_2 + 0xc) == 0) || (*(int *)(param_2 + 0xc) == 0x48)) {
      uVar2 = 0;
    }
    else {
      // Get vtable pointer from entity -0x48 offset
      if (*(int *)(param_2 + 0xc) == 0) {
        piVar4 = (int *)0x0;
      }
      else {
        piVar4 = (int *)(*(int *)(param_2 + 0xc) + -0x48);
      }
      param_2 = 0;
      // Call virtual function at vtable+0x10 with hash 0x55859efa (likely isFacingPlayer or similar)
      cVar1 = (**(code **)(*piVar4 + 0x10))(0x55859efa, &param_2);
      uVar2 = -(uint)(cVar1 != '\0') & param_2;
    }
    // If we have a valid result and some condition check passes
    if ((uVar2 != 0) && (iVar3 = FUN_007ff880(), iVar3 != 0)) {
      return;
    }
    // Set flag at +0x28 bit 0 (likely "transition pending" or "state changed")
    *(uint *)(this + 0x28) = *(uint *)(this + 0x28) | 1;
  }
  return;
}