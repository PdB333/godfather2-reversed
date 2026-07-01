// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int this, byte flags)
{
  // Call base class constructor
  FUN_00855830();
  
  // Set vtable pointer to EARSObject vtable
  *(undefined ***)(this + 0x18) = &PTR_LAB_00e355fc;
  
  // Call some initialization function (likely member initialization)
  FUN_0064d150();
  
  // If flag bit 0 is set, call destructor (this is a placement new pattern)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}