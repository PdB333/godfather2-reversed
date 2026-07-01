// FUNC_NAME: EARSObject::operatorDeleteOrFree
undefined4 __thiscall EARSObject::operatorDeleteOrFree(undefined4 this, byte flags)
{
  // Calls base destructor or cleanup (FUN_005c16e0 likely EARSObject::destructor or similar)
  FUN_005c16e0();
  
  // If flag bit 0 is set, free the memory (FUN_005c4480 likely operator delete or free)
  if ((flags & 1) != 0) {
    FUN_005c4480(this);
  }
  
  return this;
}