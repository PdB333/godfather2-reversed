// FUNC_NAME: UnknownClass::constructor
undefined4 __thiscall FUN_0082bd70(undefined4 this, byte flags)
{
  // Call base class constructor at 0x0082a380
  FUN_0082a380();
  
  // If flags & 1 (bit 0), call destructor at 0x009c8eb0
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}