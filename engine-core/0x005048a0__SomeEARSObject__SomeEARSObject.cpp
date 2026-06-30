// FUNC_NAME: SomeEARSObject::SomeEARSObject
// Address: 0x005048a0
// Role: Constructor with conditional base class call (flag param for most-derived class)
// Note: param_2 = 1 indicates this is the most-derived class, triggers base constructor

undefined4 __thiscall SomeEARSObject::SomeEARSObject(undefined4 this, byte param_2)

{
  // Call common initialization (likely sets vtable or zero-initializes members)
  FUN_005048c0();  // TODO: Rename to SomeEARSObject::initialize()
  
  // If this is the most-derived class (param_2 & 1), call base constructor
  // This pattern is typical for virtual base class support
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);  // TODO: Rename to SomeBaseClass::SomeBaseClass(SomeEARSObject*)
  }
  
  // Return this pointer as per usual constructor convention
  return this;
}