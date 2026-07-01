//FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte allocFlag)
{
  // Set vtable pointer at offset 0
  *this = &PTR_FUN_00d7251c;
  // Set vtable pointer at offset 0x3C (0xF * 4)
  this[0xF] = &PTR_LAB_00d7250c;
  // Set vtable pointer at offset 0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d72508;
  // Initialize sub-object at offset 0x50 (0x14 * 4)
  BaseClass1::constructor(this + 0x14);
  BaseClass2::constructor(this + 0x14);
  // Global engine initialization
  GlobalInit();
  // If allocFlag bit 0 is set, allocate memory for this object (size 0x6C)
  if ((allocFlag & 1) != 0) {
    operator_new(this, 0x6C);
  }
  return this;
}