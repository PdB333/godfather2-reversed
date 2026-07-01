// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(int *this)
{
  // Call base class constructor or initialization routine
  FUN_00932ce0();

  // Call virtual method at vtable offset 0x2c (likely initialize or postConstruct)
  // This is a typical pattern in EARS object construction: base init then virtual init
  (**(code **)(*this + 0x2c))();
}