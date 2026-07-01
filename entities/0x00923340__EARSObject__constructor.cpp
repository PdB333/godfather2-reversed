// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject_constructor(void *this)
{
  int i;
  undefined4 *src;
  undefined4 *dst;
  
  FUN_005bf9b0();
  *(undefined4 **)((int)this + 0x4C) = &PTR_LAB_00d86ea0;  // +0x4C vtable pointer
  DAT_01130064 = this;  // global singleton pointer
  *(undefined4 **)this = &PTR_FUN_00d86ed0;  // +0x00 vtable
  *(undefined4 **)((int)this + 0x10) = &PTR_LAB_00d86ea8;  // +0x10
  *(undefined4 **)((int)this + 0x4C) = &PTR_LAB_00d86ea4;  // +0x4C vtable (overwritten)
  src = &DAT_00e54db8;  // source data for initialization
  dst = (undefined4 *)((int)this + 0x50);  // +0x50 start of data block
  for (i = 0x13; i != 0; i = i + -1) {
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
  }
  return;
}