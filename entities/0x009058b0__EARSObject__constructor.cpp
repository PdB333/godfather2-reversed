// FUNC_NAME: EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(undefined4 this, byte flags)
{
  // Call base constructor
  FUN_00905830();  // likely EARSBaseObject::constructor
    
  // If the second parameter has bit 0 set, call additional initialization
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // likely allocation or additional setup
  }
  
  return this;
}