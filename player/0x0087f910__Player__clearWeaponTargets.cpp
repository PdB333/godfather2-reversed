// FUNC_NAME: Player::clearWeaponTargets
undefined4 __thiscall Player::clearWeaponTargets(int this, int *targetList)
{
  undefined4 result;
  
  result = 0;
  if ((targetList != (int *)0x0) &&
     ((((*(int *)(this + 0x188) != 0 || (*(int *)(this + 0x18c) != 0)) ||
       (*(int *)(this + 400) != 0)) || (*(int *)(this + 0x194) != 0)))) {
    // Call virtual function at vtable+0xb0 on each target to clear it
    // Targets are stored at offsets +0x188, +0x18c, +0x190, +0x194
    (**(code **)(*targetList + 0xb0))((int *)(this + 0x188),0);
    result = 1;
  }
  return result;
}