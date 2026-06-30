// FUNC_NAME: CombatConditionChecker::canTarget

bool __thiscall CombatConditionChecker::canTarget(int param_1, int param_2)
{
  char cVar1;
  
  // Check target type matches required type
  // param_1+0x04: m_requiredTargetType
  // param_1+0x08: m_optionalTargetType (0 means any)
  // param_2+0x40: targetType
  if ((((*(int *)(param_2 + 0x40) == *(int *)(param_1 + 4)) ||
       ((*(int *)(param_2 + 0x40) != *(int *)(param_1 + 8) && (*(int *)(param_1 + 4) == 0)))) &&
      // Check if target is valid (alive, not hidden, etc.)
      (cVar1 = FUN_006b81b0(*(undefined4 *)(param_2 + 0x48)), cVar1 != '\0')) &&
     // Check distance/range threshold
     // param_1+0x1c: m_maxDistanceSq
     // param_2+0x50: distanceSq
     ((*(uint *)(param_1 + 0x1c) <= *(uint *)(param_2 + 0x50) &&
      // Check target category mask
      // param_1+0x20: m_targetCategoryBitmask
      // param_2+0xc4: categoryIndex
      (((*(uint *)(param_1 + 0x20) == 0 ||
        ((*(uint *)(param_1 + 0x20) & 1 << ((byte)*(undefined4 *)(param_2 + 0xc4) & 0x1f)) != 0)) &&
       // Check if target is within view cone
       (cVar1 = FUN_006b7f60(*(undefined4 *)(param_2 + 0x34)), cVar1 != '\0')))))) {
    // Final line-of-sight check
    cVar1 = FUN_006b7fd0(*(undefined4 *)(param_2 + 0xd4));
    if (cVar1 != '\0') {
      return true;
    }
  }
  return false;
}