// FUNC_NAME: ResourceHolder::~ResourceHolder
undefined4 * __thiscall ResourceHolder::~ResourceHolder(undefined4 *this, byte flags)
{
  char cVar1;
  
  *this = &PTR_FUN_00e3e78c; // set vtable to derived class vtable
  BaseClass::~BaseClass(); // call base destructor (FUN_005c0360)
  this[3] = 0; // +0x0C: m_field3 = 0
  this[2] = 0; // +0x08: m_field2 = 0
  if (this[1] != 0) { // +0x04: m_pResource
    // call release via vtable from global allocator (DAT_012234ec + 4)
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this[1], 0);
  }
  this[1] = 0; // +0x04: m_pResource = 0
  *this = &PTR_LAB_00e3e74c; // set vtable to base class vtable
  if ((flags & 1) != 0) {
    cVar1 = FUN_005c43d0(this); // custom deallocation check
    if (cVar1 == '\0') {
      // call delete via vtable from global allocator
      (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(this, 0);
    }
  }
  return this;
}