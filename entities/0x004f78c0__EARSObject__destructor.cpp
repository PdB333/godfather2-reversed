// FUNC_NAME: EARSObject::destructor
undefined4 * __thiscall EARSObject::destructor(undefined4 *this, byte flags)

{
  int *refCount;
  
  if (this[8] != 0) {                         // +0x20: pointer to shared reference count
    refCount = (int *)(this[8] + 4);           // +0x4 offset from shared ref count block
    *refCount = *refCount + -1;
    if (((int *)this[8])[1] == 0) {           // if ref count reached zero
      (**(code **)(*(int *)this[8] + 4))();    // call destructor for the shared ref count object
    }
    this[8] = 0;
  }
  *this = &PTR_LAB_00e3729c;                  // set vtable pointer
  if ((flags & 1) != 0) {                     // if bit 0 set, call operator delete
    refCount = (int *)FUN_009c8f80();          // get operator delete function
    (**(code **)(*refCount + 4))(this,0);      // delete this object
  }
  return this;
}