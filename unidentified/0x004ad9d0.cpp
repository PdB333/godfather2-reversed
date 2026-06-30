// FUN_NAME: EARSObject::EARSObject
undefined4 * __thiscall EARSObject::EARSObject(undefined4 *this, undefined4 handle, int *baseObject)
{
  undefined4 uVar1;
  undefined4 localBuf[3]; // 12-byte buffer, possibly for GUID or hash
  
  this[0] = baseObject;                          // +0x00: pointer to base (data) object
  localBuf[0] = 0;
  localBuf[1] = 0;
  localBuf[2] = 0;
  uVar1 = FUN_004265d0(localBuf, baseObject);    // get type ID or hash from base object
  this[4] = uVar1;                               // +0x10: type identifier
  this[5] = baseObject;                          // +0x14: duplicate base pointer
  // Call base object's second virtual method (vtable index 2) — likely postConstruction or init
  (*(void (**)(void))(*baseObject + 8))();
  this[1] = 0;                                   // +0x04: zeroed
  this[3] = 0;                                   // +0x0C: zeroed
  this[2] = 0;                                   // +0x08: zeroed
  this[6] = handle;                              // +0x18: handle/ID passed in
  this[7] = 0;                                   // +0x1C: zeroed
  // Call base object's second virtual method again (after field setup)
  (*(void (**)(void))(*(int *)this[0] + 8))();
  uVar1 = FUN_004dafd0(handle);                  // possibly refCount / addRef
  this[8] = uVar1;                               // +0x20: reference count or handle index
  return this;
}