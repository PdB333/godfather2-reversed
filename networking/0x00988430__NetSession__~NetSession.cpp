// FUNC_NAME: NetSession::~NetSession
undefined4 * __thiscall NetSession_destructor(undefined4 *this, byte param_2)

{
  *this = &PTR_FUN_00d91070;
  this[4] = &PTR_LAB_00d91048;
  this[0x13] = &PTR_LAB_00d91044;  // +0x4C: soundStreamManager?
  if (this[0x30] != 0) {           // +0xC0: some manager pointer
    FUN_009c8f10(this[0x30]);      // cleanup that manager
  }
  this[0x13] = &PTR_LAB_00d91040; // +0x4C: null out pointer
  DAT_011305b0 = 0;               // global net session flag
  FUN_005c16e0();                 // cleanup networking resources
  if ((param_2 & 1) != 0) {
    FUN_005c4480(this);           // operator delete
  }
  return this;
}