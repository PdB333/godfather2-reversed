// FUNC_NAME: SomeClass::Constructor
undefined4 * __thiscall SomeClass::Constructor(undefined4 *this, byte allocFlag)
{
  // Set vtable pointers for multiple inheritance
  // Offset 0x0: primary vtable (PTR_FUN_00d60c30)
  *this = &PTR_FUN_00d60c30;
  // Offset 0x3C (0xF * 4): vtable for second base class
  this[0xf] = &PTR_LAB_00d60c20;
  // Offset 0x48 (0x12 * 4): vtable for third base class
  this[0x12] = &PTR_LAB_00d60c1c;
  // Offset 0x50 (0x14 * 4): vtable for fourth base class
  this[0x14] = &PTR_LAB_00d60c18;

  // Call base class constructor with its vtable
  FUN_006fc4c0(&LAB_006fec60, this);

  // Check flag at offset 0xE8 (0x3A * 4)
  if (this[0x3a] != 0) {
    // If flag is set, enable some feature (argument 1)
    FUN_00474680(1);
  }

  // Perform additional initialization
  FUN_00474090();

  // If allocFlag bit 0 is set, allocate memory for this object (size 0x160)
  if ((allocFlag & 1) != 0) {
    FUN_0043b960(this, 0x160);
  }

  return this;
}