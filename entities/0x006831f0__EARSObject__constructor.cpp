// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base class constructor
  FUN_006828a0();
  
  // If the low bit of flags is set, call the destructor (placement delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}