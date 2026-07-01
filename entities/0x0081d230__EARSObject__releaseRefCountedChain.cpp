// FUNC_NAME: EARSObject::releaseRefCountedChain
void __fastcall EARSObject::releaseRefCountedChain(undefined4 *this)
{
  // +0x14 (param_1[5]): pointer to child object (level 2)
  if (this[5] != 0) {
    // vtable+4 = release() method
    (**(code **)(*(int *)this[4] + 4))(this[5], 0);
    this[5] = 0;
  }
  // vtable+0xc = destructor/cleanup for level 1
  (**(code **)(*(int *)this[4] + 0xc))();

  // +0xc (param_1[3]): pointer to child object (level 1)
  if (this[3] != 0) {
    (**(code **)(*(int *)this[2] + 4))(this[3], 0);
    this[3] = 0;
  }
  // vtable+0xc = destructor/cleanup for level 0
  (**(code **)(*(int *)this[2] + 0xc))();

  // +0x4 (param_1[1]): pointer to child object (level 0)
  if (this[1] != 0) {
    (**(code **)(*(int *)*this + 4))(this[1], 0);
    this[1] = 0;
  }
  // vtable+0xc = destructor/cleanup for root
  (**(code **)(*(int *)*this + 0xc))();
}