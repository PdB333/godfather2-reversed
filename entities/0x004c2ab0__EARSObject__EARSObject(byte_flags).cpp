// FUNC_NAME: EARSObject::EARSObject(byte flags)
EARSObject * __thiscall EARSObject::EARSObject(EARSObject *this, byte flags)
{
  // Set vtable to the class's vtable (address 0x00e36220)
  this->vtable = &PTR_FUN_00e36220;

  // Call base class constructor or member initialization
  FUN_004c29a0();                    // Base initializer (likely EARSObject base)

  // If the sub-object pointer at offset 0x208 (+0x208) is not null, free it
  // This suggests the class manages a dynamically allocated sub-object
  if (this->subObjectPtr != 0) {
    FUN_009c8f10(this->subObjectPtr);  // Free the sub-object memory
  }

  // Additional initialization (member fields, etc.)
  FUN_004c27f0();                    // Secondary initialization

  // If the flags have bit 0 set, deallocate the entire object
  // This pattern is unusual for a constructor but may indicate a combined
  // constructor/destructor or a placement delete on exception
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);             // Operator delete / free this object
  }

  return this;
}