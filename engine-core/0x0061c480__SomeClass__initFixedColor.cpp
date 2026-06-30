// FUNC_NAME: SomeClass::initFixedColor
void __fastcall SomeClass::initFixedColor(int this)
{
  undefined4 uVar1;
  
  uVar1 = FUN_0060a380();
  *(undefined4 *)(this + 0x10) = uVar1; // +0x10: some resource handle
  uVar1 = FUN_0060a2e0(&PTR_DAT_00f10fec);
  *(undefined4 *)(this + 0x14) = uVar1; // +0x14: another resource handle
  FUN_006127d0(); // likely a setup/init call
  uVar1 = FUN_0060a580(*(undefined4 *)(this + 0x10), "FixedColor"); // get something by name "FixedColor"
  *(undefined4 *)(this + 0xc0) = uVar1; // +0xc0: store the FixedColor reference
  return;
}