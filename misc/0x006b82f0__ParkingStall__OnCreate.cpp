// FUNC_NAME: ParkingStall::OnCreate
undefined4 * __thiscall ParkingStall_OnCreate(undefined4 *this, undefined4 param_2)
{
  // Call base class constructor (likely EARSObject::OnCreate or similar)
  FUN_0046c590(param_2);
  
  // Set vtable pointer
  *this = &PTR_FUN_00d5e5b8;
  
  // Init member fields at known offsets
  this[0xf] = &PTR_LAB_00d5e5a8;  // +0x3C - some callback/function pointer
  this[0x12] = &PTR_LAB_00d5e5a4; // +0x48 - another callback/function pointer
  this[0x14] = 0;                 // +0x50 - pointer, null init
  *(undefined2 *)(this + 0x15) = 0;  // +0x54 - 2-byte field (maybe short/Flags)
  *(undefined2 *)((int)this + 0x56) = 0; // +0x56 - another 2-byte field (padding or flags)
  this[0x16] = 0;                 // +0x58 - pointer, null init
  this[0x17] = 0;                 // +0x5C - pointer, null init
  this[0x18] = 0;                 // +0x60 - pointer, null init
  this[0x19] = 0;                 // +0x64 - pointer, null init
  
  return this;
}