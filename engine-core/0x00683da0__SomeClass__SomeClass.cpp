// FUNC_NAME: SomeClass::SomeClass
undefined4 * __thiscall SomeClass::SomeClass(undefined4 *this, byte allocFlag)
{
  // Set vtable pointers for multiple inheritance
  *this = &PTR_FUN_00d5885c;          // Primary vtable at offset 0
  this[0xf] = &PTR_LAB_00d5884c;     // Secondary vtable at offset 0x3C (15*4)
  this[0x12] = &PTR_LAB_00d58848;    // Tertiary vtable at offset 0x48 (18*4)

  // Call base class initialization (global function, no this)
  baseInit();

  // If allocFlag bit 0 is set, perform additional memory handling (e.g., placement delete)
  if ((allocFlag & 1) != 0) {
    handleAllocation(this, 0x50);     // Size 0x50 = 80 bytes
  }

  return this;
}