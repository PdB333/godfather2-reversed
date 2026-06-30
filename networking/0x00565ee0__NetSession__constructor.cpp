// FUNC_NAME: NetSession::constructor
undefined4 * __fastcall NetSession::constructor(undefined4 *this)
{
  DAT_012234dc = this;
  *this = &PTR_FUN_00e3a5d0; // vtable pointer
  FUN_00ae9710(); // base class constructor
  this[0x2011] = 0; // +0x8044: some flag
  *(undefined1 *)(this + 0x2012) = 1; // +0x8048: byte flag
  this[0x2005] = 0x8000; // +0x8014: buffer size or max value
  FUN_00adbf50(); // initialize network subsystem
  this[0x2004] = this + 1; // +0x8010: pointer to self+4 (likely a buffer start)
  this[0x200f] = 1; // +0x803c: some count or flag
  return this;
}