// FUNC_NAME: UnknownClass::destructor
void __fastcall SomeClass__Destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d74820;
  this[1] = &PTR_LAB_00d747f8;
  if (this[0xf] != 0) {
    FUN_00848cc0(); // Probably operator delete[] or similar cleanup
  }
  if (this[0x10] != 0) {
    FUN_00848cc0(); // Probably operator delete[] or similar cleanup
  }
  if (this[0x11] != 0) {
    FUN_00848cc0(); // Probably operator delete[] or similar cleanup
  }
  FUN_00596640(); // Probably some base class destructor
  *this = &PTR_LAB_00d74620;
  return;
}