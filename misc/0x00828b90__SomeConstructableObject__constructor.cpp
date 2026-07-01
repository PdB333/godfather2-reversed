// FUNC_NAME: SomeConstructableObject::constructor
int __thiscall SomeConstructableObject::constructor(int this, byte flags)
{
  // call base constructor at this+4 and this+8 or something
  FUN_008285c0(*(undefined4 *)(this + 4), *(undefined4 *)(this + 8));
  
  // +0x0C counter / state flag initialized to 0
  *(undefined4 *)(this + 0xc) = 0;
  
  // If count at +0x08 > 1, call something on first member
  // +0x08 likely tracks number of sub-objects or ref count
  if (1 < *(uint *)(this + 8)) {
    FUN_009c8f10(*(undefined4 *)(this + 4));
  }
  
  // If flag bit 0 set, delete this object (placement new free?)
  // Common pattern for operator delete if constructed via placement new with flag
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}