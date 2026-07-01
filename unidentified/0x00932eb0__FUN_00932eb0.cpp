// FUNC_NAME: SomeClass::initialize
void __thiscall SomeClass::initialize(int this, undefined4 param2, undefined4 param3)
{
  FUN_004d3d90(param2); // likely release or cleanup
  FUN_004d3d90(param3); // likely release or cleanup
  DAT_00e5672c = 0x18; // set some global state to 24
  *(undefined4 *)(this + 0x60) = 0; // clear member at +0x60
  if ((DAT_01130590 & 1) == 0) {
    FUN_005c0d50(this + 0x14, &LAB_00931e00, 0); // register callback at this+0x14 with label
    DAT_01130590 = DAT_01130590 | 1; // mark as initialized
  }
  return;
}