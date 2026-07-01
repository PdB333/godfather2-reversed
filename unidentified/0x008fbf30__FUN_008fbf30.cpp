// FUNC_NAME: UnknownClass::destructor
void __fastcall UnknownClass_destructor(undefined4 *this)
{
  *this = &PTR_FUN_00d81474;
  this[0xf] = &PTR_LAB_00d81464;
  this[0x12] = &PTR_LAB_00d81460;
  FUN_004086d0(&DAT_0120e93c);
  FUN_008fc950(this);
  FUN_004086d0(&DAT_0120e970);
  FUN_004086d0(this + 0x43);
  FUN_00408310(this + 0x43);
  FUN_00408310(this + 0x45);
  FUN_00408310(this + 0x47);
  FUN_00408310(this + 0x49);
  if (this[0x18] != 0) {
    (*(code *)this[0x1b])(this[0x18]);
  }
  if (this[0x14] != 0) {
    (*(code *)this[0x17])(this[0x14]);
  }
  FUN_0046c640();
  return;
}