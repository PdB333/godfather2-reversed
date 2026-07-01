// FUNC_NAME: Entity::clearPendingAnimations
undefined4 __thiscall Entity::clearPendingAnimations(int this, int *param_2)
{
  undefined4 result;
  
  result = 0;
  // Check if param_2 is valid and if any of the animation slots (0x178-0x184) are non-zero
  // These offsets likely represent pending animation handles or flags
  if ((param_2 != (int *)0x0) &&
     ((((*(int *)(this + 0x178) != 0 || (*(int *)(this + 0x17c) != 0)) ||
       (*(int *)(this + 0x180) != 0)) || (*(int *)(this + 0x184) != 0)))) {
    // Call virtual function at vtable offset 0xb0 on param_2, passing pointer to animation slot 0x178 and 0
    // This likely stops/clears the animation at that slot
    (**(code **)(*param_2 + 0xb0))((int *)(this + 0x178),0);
    result = 1;
  }
  return result;
}