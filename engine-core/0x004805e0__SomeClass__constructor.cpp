// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(SomeClass *this)
{
  // +0x00: primary vtable pointer
  this->vtable = &PTR_FUN_00e333b8;
  // +0x3C: secondary vtable pointer (likely for an interface or derived class)
  this->vtable2 = &PTR_LAB_00e333d4;
  // +0x48: tertiary vtable pointer (another interface)
  this->vtable3 = &PTR_LAB_00e333e4;

  // +0x14: sub-object (probably a container or string table)
  // Initialize the sub-object (constructor call)
  FUN_004086d0(reinterpret_cast<SubObjectType*>(&this->subObject));
  // Perform additional initialization on the sub-object
  FUN_00408310(reinterpret_cast<SubObjectType*>(&this->subObject));

  // Global one-time initialization (singleton or static state)
  FUN_0046c640();
}