// FUNC_NAME: Animated::constructor
undefined4 __thiscall Animated::constructor(Animated *this, byte flags)
{
  // Call base class constructor at 0x784cb0 (likely Entity or Destructible)
  Entity::constructor(this);
  
  // If bit 0 of flags is set, call operator delete at offset 0x45c (0x45c bytes after this, probably a member like m_pName or m_pData)
  if ((flags & 1) != 0) {
    // FUN_0043b960 is operator delete[] or free, +0x45c is size of some array member
    operatorDelete((void *)((int)this + 0x45c)); // +0x45c: array/buffer member
  }
  
  return (undefined4)this;
}