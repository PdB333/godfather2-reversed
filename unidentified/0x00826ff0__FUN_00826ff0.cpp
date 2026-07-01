// FUNC_NAME: SomeClass::SomeClass

undefined4 __thiscall SomeClass::SomeClass(byte allocateFlag)
{
  // Call base class constructor or initialization routine
  this->initializeBase();   // FUN_00826820

  // If allocateFlag has bit 0 set, allocate extra memory block of size 0xb4 (180 bytes)
  if ((allocateFlag & 1) != 0) {
    this->allocateInternalBuffer(0xb4);   // FUN_0043b960 - likely allocation, returns pointer but not used here
  }

  return this;
}