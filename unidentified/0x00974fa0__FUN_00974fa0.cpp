// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d8f840;
  this[4] = &PTR_LAB_00d8f818;  // +0x10 - vtable for base class?
  this[0x13] = &PTR_LAB_00d8f808;  // +0x4C
  this[0x16] = &PTR_LAB_00d8f804;  // +0x58
  
  FUN_004086d0(&DAT_0112ffd4);  // DAT_0112ffd4 - likely a global spinlock/mutex
  FUN_004086d0(&DAT_0112fe30);  // DAT_0112fe30 - another mutex
  FUN_004086d0(&DAT_0112fe20);  // DAT_0112fe20 - another mutex
  
  this[0x16] = &PTR_LAB_00d8f800;  // +0x58 update vtable pointer?
  
  DAT_01130598 = 0;  // global flag - set to false/off
  FUN_004083d0();      // some initialization function
  FUN_005c16e0();      // possibly allocate pool or initialize memory
  
  return;
}