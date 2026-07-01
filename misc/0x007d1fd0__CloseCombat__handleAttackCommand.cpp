// FUNC_NAME: CloseCombat::handleAttackCommand
undefined4 __thiscall CloseCombat::handleAttackCommand(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 commandType, undefined4 param_6)
{
  char isActive;
  undefined4 result;
  float animationTime;
  
  switch(commandType) {
  case 0x31: // COMMAND_START_ATTACK
    FUN_007d1a70(); // startAttack
    break;
  case 0x32: // COMMAND_STOP_ATTACK
    FUN_007d1c70(); // stopAttack
    return 1;
  case 0x33: // COMMAND_CHECK_ATTACK
    isActive = FUN_00481620(); // isCombatActive
    if (isActive != '\0') {
      FUN_007d1d90(); // getCurrentAttackAnimationTime
      *(float *)(this + 0x80) = (float)animationTime; // +0x80 lastAttackTime
      return 1;
    }
    break;
  case 0x34: // COMMAND_PLAY_SPECIAL
    isActive = FUN_00481620(); // isCombatActive
    if (isActive != '\0') {
      FUN_007d1f20(param_3); // playSpecialAnimation
      return 1;
    }
    break;
  default:
    result = FUN_007abec0(param_2, param_3, param_4, commandType, param_6); // handleBaseCommand
    return result;
  }
  return 1;
}