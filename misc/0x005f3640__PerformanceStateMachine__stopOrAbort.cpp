// FUNC_NAME: PerformanceStateMachine::stopOrAbort
void __thiscall PerformanceStateMachine::stopOrAbort(int this, int param_2)
{
  int *piVar1;
  int iVar2;
  bool bVar3;
  char *pcVar4;
  int *piVar5;
  
  if (this == 0) {
    return;
  }
  piVar1 = (int *)(this + 0xc + (uint)*(byte *)(this + 0x6f) * 4);
  bVar3 = true;
  piVar5 = (int *)(this + 0xc);
  if (param_2 == 1) { // abort = true
    // Clear all active performances in the array
    for (; piVar5 < piVar1; piVar5 = piVar5 + 1) {
      if (*piVar5 != 0) {
        FUN_005f16b0(); // some cleanup function
        *piVar5 = 0;
      }
    }
    // Clear flags at +0x6c (bitmask), set state to PERFORMANCE_STATE_STOPPED
    *(ushort *)(this + 0x6c) = *(ushort *)(this + 0x6c) & 0xff87;
    *(undefined4 *)(this + 0x68) = 5; // PERFORMANCE_STATE_STOPPED
  }
  else { // stop (graceful)
    // Iterate through performances and check if any are still active
    if (piVar5 < piVar1) {
      do {
        iVar2 = *piVar5;
        if (iVar2 != 0) {
          if ((*(byte *)(iVar2 + 0x10) & 0x40) == 0) { // not stopped/finished?
            // Stop the animation/audio via some object at DAT_01223510
            (**(code **)(*DAT_01223510 + 0x24))(*(undefined2 *)(iVar2 + 8));
            FUN_005dbc10(*(undefined2 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0x18));
            FUN_005f1660(); // perform stop logic
          }
          bVar3 = false; // at least one performance still active
        }
        piVar5 = piVar5 + 1;
      } while (piVar5 < piVar1);
      if (!bVar3) {
        // Still have active performances, set state to STOPPING
        *(undefined4 *)(this + 0x68) = 4; // PERFORMANCE_STATE_STOPPING
        goto LAB_005f36f2;
      }
    }
    // No active performances left, set to STOPPED
    *(undefined4 *)(this + 0x68) = 5; // PERFORMANCE_STATE_STOPPED
  }
LAB_005f36f2:
  pcVar4 = "PERFORMANCE_STATE_STOPPED";
  if (*(int *)(this + 0x68) != 5) {
    pcVar4 = "PERFORMANCE_STATE_STOPPING";
  }
  FUN_005dbc10(pcVar4); // log state change
  return;
}