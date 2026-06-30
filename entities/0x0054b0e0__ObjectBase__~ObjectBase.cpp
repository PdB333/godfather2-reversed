// FUNC_NAME: ObjectBase::~ObjectBase
void __fastcall ObjectBase::~ObjectBase(undefined4 *this_)
{
  uint handle;
  
  *this_ = &PTR_FUN_00e39c48;
  handle = this_[6];
  if (-1 < (int)handle) {
    TlsGetValue(DAT_01139810); // Get thread-local allocator instance
    FUN_00aa26e0(this_[4], (handle & 0x3fffffff) * 0x60, 0x17); // Deallocate block at +0x10, size = (handle & mask) * 0x60, type 0x17
  }
  *this_ = &PTR___purecall_00dcfcf4; // Final vtable = purecall (prevent further virtual calls)
  return;
}