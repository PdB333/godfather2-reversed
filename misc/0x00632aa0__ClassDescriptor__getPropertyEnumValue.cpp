// FUNC_NAME: ClassDescriptor::getPropertyEnumValue
int __thiscall ClassDescriptor::getPropertyEnumValue(int *this) {
  int vtable;
  int classInfo;
  int baseValue;
  int elementArray;
  int idx;
  int result;

  // Check flags at offset +0x8
  if ((this[2] & 1) == 0) {
    // If flag bit 1 is set, dereference pointer at +0x10 to update current value at +0xC
    if ((this[2] & 2) != 0) {
      this[3] = *(int *)this[4];
    }
    // Get class info pointer (vtable[-4] is typical for RTTI/class descriptor)
    vtable = this[0];
    classInfo = *(int *)(vtable + -4);
    // Read base offset from classInfo + 0xC
    baseValue = *(int *)(classInfo + 0xc);
    // Compute index: (currentValue - baseValue) / 4 - 1
    idx = (this[3] - baseValue >> 2) - 1;
    if (idx >= 0) {
      // Get element array from classInfo + 0x14
      elementArray = *(int *)(classInfo + 0x14);
      if (elementArray != 0) {
        result = *(int *)(elementArray + idx * 4);
        return result;
      }
      return 0;
    }
  }
  return 0xFFFFFFFF; // -1 for invalid
}