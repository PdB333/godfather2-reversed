// FUNC_NAME: UnknownClass::constructor
undefined4 * __fastcall UnknownClassConstructor(undefined4 *this)
{
  this[1] = &PTR_LAB_00d730c4;  // vtable setup (offset +4)
  DAT_0112a688 = this;          // singleton: store pointer to instance
  *this = &PTR_FUN_00d730cc;   // vtable pointer at +0
  this[1] = &PTR_LAB_00d730c8; // second vtable pointer at +4 (seems overwritten)
  this[2] = 0;                 // member at +0x8 initialized to null
  this[3] = 0;                 // member at +0xC initialized to null
  this[4] = 0;                 // member at +0x10 initialized to null
  FUN_00463980(0x964a0392, this, 1); // register singleton with system (unknown ID)
  return this;
}