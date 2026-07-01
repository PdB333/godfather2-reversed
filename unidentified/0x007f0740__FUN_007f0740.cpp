// FUNC_NAME: SomeClass::updateSomething
void __thiscall updateSomething(int *this, int param2, int param3, int *param4, char param5)
{
  int iVar1;
  
  // Global DAT_0112bb58 is used as a base multiplier/value
  iVar1 = DAT_0112bb58;
  if (DAT_0112bb58 == 0) {
    iVar1 = param3;
  }
  // Store the computed value at this[0]
  this[0] = iVar1;
  
  // Check if param5 is false (0) OR if some global float threshold is met
  // this[0x3d] is at offset +0xF4 (0x3d * 4 = 244 = 0xF4)
  if ((param5 == '\0') ||
     (_DAT_00d5780c < (float)this[0x3d] || _DAT_00d5780c == (float)this[0x3d])) {
    // Default path: use this+1 as param4 if null
    if (param4 == (int *)0x0) {
      param4 = this + 1;
    }
    // Copy this[1] to this[2], reset this[0x3d] and this[10]
    this[2] = this[1];
    this[0x3d] = 0;
    this[10] = 0;
  }
  else {
    // Alternative path: use this+3 as param4
    param4 = this + 3;
  }
  
  if (param2 != 0) {
    // Compute address: iVar1 * 0x22c + *(param2 + 0x38)
    *param4 = iVar1 * 0x22c + *(int *)(param2 + 0x38);
    FUN_007ef360();
    return;
  }
  // Default fallback: use global DAT_00e53b50
  *param4 = (int)&DAT_00e53b50;
  FUN_007ef360();
  return;
}