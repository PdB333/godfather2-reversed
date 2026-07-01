// FUNC_NAME: UnknownClass::Constructor
void __thiscall UnknownClass::Constructor(UnknownClass *this)
{
  // Set vtable pointer (offset 0x00)
  *this = (UnknownClass)&PTR_FUN_00d92178;
  // Set secondary vtable/base pointer at offset 0x10
  *(int *)((int)this + 0x10) = (int)&PTR_LAB_00d92150;
  // Set tertiary vtable/base pointer at offset 0x4C (overwritten below)
  *(int *)((int)this + 0x4C) = (int)&PTR_LAB_00d9214c;
  // Overwrite offset 0x4C with another pointer (likely final)
  *(int *)((int)this + 0x4C) = (int)&PTR_LAB_00d92148;
  // Global flag: possibly a singleton or state indicator
  DAT_0113000c = 0;
  // Call base class initialization or global init
  FUN_005c16e0();
  return;
}