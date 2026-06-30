// FUN_0075bc40: SomeClass::SomeClass(byte flag)
// This is a constructor with a flag parameter. It calls the base class constructor (likely at 0x0075b720) and then conditionally performs additional initialization (at 0x00624da0) if the flag's lowest bit is set.

undefined4 __thiscall SomeClass::SomeClass(byte flag)
{
  // Call base class constructor
  SomeClass::baseConstructor(this);
  
  // If flag's low bit is set, perform additional setup (e.g. allocate owned resource)
  if ((flag & 1) != 0) {
    this->initializeAllocated();
  }
  
  return this;
}