// FUNC_NAME: UnknownClass::constructor
void __fastcall UnknownClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d74490;
  this[0xf] = &PTR_LAB_00d74480;
  this[0x12] = &PTR_LAB_00d7447c;
  if (this[0x16] != 0) {
    FUN_009c8c00(this[0x16]);
    this[0x16] = 0;
  }
  this[0x14] = 0;
  this[0x15] = 0;
  FUN_0083fbc0();
  return;
}