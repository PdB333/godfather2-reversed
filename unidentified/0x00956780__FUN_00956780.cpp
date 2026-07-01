// FUNC_NAME: SomeClass::destructor
undefined4 __thiscall SomeClass::destructor(undefined4 this, byte isDestructorCleanup)
{
  // Call base class destructor or cleanup logic
  SomeClassBase::~SomeClassBase();
  
  // If this is a full destructor (not just cleanup), deallocate memory
  if ((isDestructorCleanup & 1) != 0) {
    operatorDelete(this, 0x58); // Free 0x58 byte sized allocation
  }
  
  return this;
}