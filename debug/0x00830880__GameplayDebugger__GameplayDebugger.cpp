// FUNC_NAME: GameplayDebugger::GameplayDebugger
void __fastcall GameplayDebugger::constructor(int *this)
{
  // vtable setup: set the vtable pointer to 0x00d73790
  *this = (int)&PTR_FUN_00d73790;

  // Call parent/base class constructor (likely Debug or some base of GameplayDebugger)
  FUN_0082a3c0();

  // Set another vtable pointer at offset +0x30 (0xc * 4 = 48 bytes = 0x30)
  this[0xc] = (int)&PTR_LAB_00e32854;

  // Call another base class constructor or initialization routine
  FUN_00821f60();

  return;
}