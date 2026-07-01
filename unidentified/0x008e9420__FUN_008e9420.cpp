// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)
{
  *this = &PTR_FUN_00d80c78;
  this[0xf] = &PTR_LAB_00d80c68;
  this[0x12] = &PTR_LAB_00d80c64;
  this[0x14] = &PTR_LAB_00d80c60;
  this[0x15] = &PTR_LAB_00d80c00;
  this[0x16] = &PTR_LAB_00d80b98;
  FUN_004086d0(&DAT_0112a5e0); // likely some global initialization
  FUN_00408310(&DAT_0112a5e0); // likely another init
  FUN_00408310(this + 0x62);   // init sub-object at offset 0x188 (0x62*4)
  FUN_004086d0(&DAT_0112a628); // another global init
  if (this[0x68] != 0) {       // check if pointer at +0x1A0 is non-null
    FUN_004daf90(this + 0x68); // free/release that pointer
  }
  this[0xf] = &PTR_LAB_00d7fff8;  // update vtable entries
  *this = &PTR_FUN_00d80008;
  this[0x12] = &PTR_LAB_00d7fff4;
  this[0x14] = &PTR_LAB_00d7fff0;
  this[0x15] = &PTR_LAB_00d7ff90;
  this[0x16] = &PTR_LAB_00d7ff28;
  FUN_0046ea20(); // final initialization step
  return;
}