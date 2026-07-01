// FUNC_NAME: PlayerF2FSM::checkTransitionCondition
undefined1 __thiscall PlayerF2FSM::checkTransitionCondition(int this, undefined4 transitionId)
{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  undefined1 result;
  
  result = 0;
  // +0x1dc: some float state variable (e.g., velocity or timer)
  bVar1 = *(float *)(this + 0x1dc) <= DAT_00d6bfe0;
  // +0x1e0: another float state variable
  bVar4 = *(float *)(this + 0x1e0) <= DAT_00d6bfe0;
  
  switch(transitionId) {
  case 1: // Transition type 1 (e.g., idle->walk)
    bVar4 = *(float *)(this + 0x1c4) == 0.0;
    bVar2 = 0.0 < *(float *)(this + 0x1c4);
    break;
  case 2: // Transition type 2 (e.g., walk->run)
    bVar2 = DAT_00d6bfe8 == *(float *)(this + 0x1c4);
    bVar3 = DAT_00d6bfe8 < *(float *)(this + 0x1c4);
    goto LAB_007b0881;
  case 3: // Transition type 3 (e.g., run->sprint)
    if (*(float *)(this + 0x1c4) < DAT_00d6bfe8) {
      return 0;
    }
    if (DAT_00d6bfe4 < *(float *)(this + 0x1c4)) {
      return 0;
    }
    goto LAB_007b08cb;
  case 4: // Transition type 4 (e.g., sprint->run)
    bVar2 = *(float *)(this + 0x1c4) == DAT_00d6bfe4;
    bVar3 = *(float *)(this + 0x1c4) < DAT_00d6bfe4;
LAB_007b0881:
    if (bVar3 || bVar2) {
      return 0;
    }
    // +0x1c8: another float state (e.g., stamina or cooldown)
    if (DAT_00d5f79c < *(float *)(this + 0x1c8)) {
      return 0;
    }
    if (bVar1) goto LAB_007b08cb;
    goto LAB_007b08cd;
  case 5: // Transition type 5 (e.g., sprint->idle)
    bVar4 = *(float *)(this + 0x1c4) == _DAT_00d577a0;
    bVar2 = *(float *)(this + 0x1c4) < _DAT_00d577a0;
    break;
  default:
    goto switchD_007b0835_default;
  }
  if ((!bVar2 && !bVar4) && (bVar4 = bVar1, DAT_00d5f79c < *(float *)(this + 0x1c8))) {
LAB_007b08cb:
    if (!bVar4) {
LAB_007b08cd:
      // Call to perform the actual state transition
      FUN_007af6c0();
      result = 1;
    }
  }
switchD_007b0835_default:
  return result;
}