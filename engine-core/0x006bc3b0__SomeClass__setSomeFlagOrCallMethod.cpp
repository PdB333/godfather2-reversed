// FUNC_NAME: SomeClass::setSomeFlagOrCallMethod
void __thiscall SomeClass::setSomeFlagOrCallMethod(int thisPtr, int param_2, char param_3)
{
  // Check if a flag at offset +0x180 is not negative (i.e., bit 31 is clear)
  if (-1 < *(int *)(thisPtr + 0x180)) {
    // If there's a pointer at +0x130, use it
    if (*(int **)(thisPtr + 0x130) != (int *)0x0) {
      // If param_2 is 2, map it to 1
      if (param_2 == 2) {
        param_2 = 1;
      }
      // Call a virtual function at vtable offset 0x44 (0x44 / 4 = 0x11th entry)
      // The first argument is a constant 0xf86f4484 (likely a hash or identifier)
      (**(code **)(**(int **)(thisPtr + 0x130) + 0x44))(0xf86f4484, param_2);
    }
    // If param_3 is non-zero, set bit 31 of the flag at +0x180
    if (param_3 != '\0') {
      *(uint *)(thisPtr + 0x180) = *(uint *)(thisPtr + 0x180) | 0x80000000;
      return;
    }
    // Otherwise, clear bit 31 of the flag at +0x180
    *(uint *)(thisPtr + 0x180) = *(uint *)(thisPtr + 0x180) & 0x7fffffff;
  }
  return;
}