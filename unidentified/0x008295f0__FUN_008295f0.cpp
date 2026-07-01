// FUNC_NAME: BaseClass::constructor
undefined4 * __fastcall BaseClass::constructor(undefined4 *this)

{
  FUN_008334a0();
  *this = &PTR_LAB_00d7366c;
  *(undefined8 *)(this + 0x18) = 0; // +0x18: field_18
  *(undefined8 *)(this + 0x1a) = 0; // +0x1a: field_1a
  *(undefined8 *)(this + 0x1c) = 0; // +0x1c: field_1c
  *(undefined8 *)(this + 0x1e) = 0; // +0x1e: field_1e
  FUN_009cbee0();
  return this;
}