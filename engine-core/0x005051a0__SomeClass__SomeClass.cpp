// FUNC_NAME: SomeClass::SomeClass
undefined4 __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
  baseInit(); // FUN_005051c0 - likely base class or core initialization
  if ((flag & 1) != 0) {
    cleanupObject(this); // FUN_009c8eb0 - possibly cleanup/deallocation
  }
  return this;
}