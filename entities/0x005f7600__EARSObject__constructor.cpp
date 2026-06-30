// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte param_2)

{
  // Call base class constructor at 0x005f7620
  FUN_005f7620();
  
  // If the flag bit 0 is set, call the destructor (placement delete)
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}