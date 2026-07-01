// FUNC_NAME: SomeClass::SomeClass
void __thiscall SomeClass::SomeClass(SomeClass *this)
{
  // Set primary vtable (likely this class's vtable)
  *(int *)this = (int)&PTR_FUN_00d7388c;
  // Call first base constructor or initialization
  FUN_0082ba50();
  // Set secondary vtable at offset 0x30 (param_1[0xc] -> 12 * 4 = 48 = 0x30)
  *(int *)((char *)this + 0x30) = (int)&PTR_LAB_00e32854;
  // Call second initialization
  FUN_00821f60();
}