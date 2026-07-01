// FUNC_NAME: PlayerActionableTargetSM::tryAction
undefined4 __thiscall PlayerActionableTargetSM::tryAction(int this, int target, int actionType, undefined4 param4, undefined4 param5)

{
  char cVar1;
  
  *(undefined4 *)(this + 0x44) = DAT_01205228; // +0x44: some state/flag, set to global constant
  cVar1 = FUN_008a4380(); // likely isPlayerInVehicle() or similar
  if ((((cVar1 == '\0') && (*(char *)(target + 0x1a5) == '\0')) && // +0x1A5: target is not dead/disabled
      (((uint)(*(int *)(this + 0x24) - *(int *)(this + 0x30)) < 4 || (actionType != 0)))) && // +0x24/+0x30: distance check or cooldown
     (*(int *)(this + 0x18) != 0)) { // +0x18: some required component exists
    cVar1 = FUN_008e4d10(actionType, param4, param5); // likely validateAction
    if (cVar1 != '\0') {
      FUN_008e6640(&target); // likely executeAction
      return 1;
    }
  }
  return 0;
}