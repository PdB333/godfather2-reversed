// FUNC_NAME: SomeClass::SomeClass
// Function address: 0x006ace20
// Role: Constructor for SomeClass, calls base constructor then optionally performs cleanup if allocated

undefined4 __thiscall SomeClass::SomeClass(undefined4 this, byte allocFlag)
{
  // Call base class constructor
  FUN_006ac960(); // likely BaseClass::BaseClass()
  
  // If object was heap-allocated (allocFlag bit 0 set), perform additional cleanup/registration
  if ((allocFlag & 1) != 0) {
    FUN_009c8eb0(this); // possibly operator delete or deregister
  }
  
  return this;
}