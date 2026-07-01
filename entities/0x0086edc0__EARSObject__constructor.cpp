// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flags)
{
  int iVar1;
  
  *this = &PTR_LAB_00d75f7c;
  this[0x18] = &PTR_LAB_00d75f68;
  if (this[0x17] != 0) {
    iVar1 = FUN_0043b870(DAT_01131018);
    if (iVar1 != 0) {
      FUN_009af0a0(this + 0x18);
    }
  }
  FUN_0086aff0();
  if ((flags & 1) != 0) {
    FUN_00624da0(this);
  }
  return this;
}