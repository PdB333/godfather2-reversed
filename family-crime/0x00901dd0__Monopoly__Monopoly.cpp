// FUNC_NAME: Monopoly::Monopoly
void __fastcall Monopoly::Monopoly(undefined4 *this)
{
  *this = &PTR_FUN_00d81c20;
  this[0xf] = &PTR_LAB_00d81c10;
  this[0x12] = &PTR_LAB_00d81c0c;
  FUN_004086d0(this + 0x14); // initialize some sub-object at offset +0x50 (0x14 * 4)
  FUN_00408310(this + 0x14); // additional sub-object setup
  FUN_00408310(this + 0x16); // another sub-object at +0x58
  FUN_0046c640(); // probably Monopoly::setup or similar init
  return;
}