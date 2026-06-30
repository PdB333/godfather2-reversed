// FUNC_NAME: EARSObject::destructor
int __thiscall EARSObject::destructor(int this, byte flags)
{
  // Call the base destructor or cleanup function on the object at offset +0x8
  FUN_009c8f10(*(undefined4 *)(this + 8));
  
  // If the low bit of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}