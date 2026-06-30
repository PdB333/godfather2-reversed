// FUNC_NAME: SomeClass::constructor (address 0x0046b420)
// This is a constructor for a derived class. It sets the vtable pointer to the
// base class vtable, calls the base constructor, then switches to the derived
// class vtable. If the object was allocated with operator new (param_2 & 1),
// it calls a cleanup function that likely frees memory on failure.
// Base constructor: FUN_0043e380 (0x43e380)
// Cleanup function: FUN_009c8eb0 (0x9c8eb0)

class SomeBaseClass;
class SomeDerivedClass;

void __thiscall SomeDerivedClass::constructor(SomeDerivedClass* this, byte allocatedFlag)
{
  // Set vtable to base class vtable
  *((int**)this) = (int*)&PTR_FUN_00e326b4;
  
  // Call base constructor (FUN_0043e380)
  FUN_0043e380(this);
  
  // Switch vtable to derived class vtable
  *((int**)this) = (int*)&PTR_LAB_00e30ea0;
  
  // If allocatedFlag indicates memory was allocated (bit 0 set),
  // call the cleanup function (likely a placement delete or destructor)
  if ((allocatedFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return;
}