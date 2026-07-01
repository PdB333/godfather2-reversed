// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)
{
  short refCount;
  
  refCount = *(short *)((int)this + 0x12);  // +0x12: reference count
  *this = &PTR_FUN_00d6ffac;  // set vtable pointer
  while (refCount != 0) {
    FUN_00408090();  // likely decrementRefCount or release
    refCount = *(short *)((int)this + 0x12);
  }
  if (((undefined4 *)this[2] != (undefined4 *)0x0) && ((*(byte *)(this + 6) & 1) == 0)) {
    (*(code *)**(undefined4 **)this[2])(1);  // call vtable function on child object
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete
  }
  return this;
}