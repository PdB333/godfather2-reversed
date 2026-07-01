// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte param_2)

{
  int iVar1;
  int *piVar2;
  
  *this = &PTR_FUN_00d7ca70;
  iVar1 = FUN_006101a0();
  if (iVar1 != 0) {
    FUN_00610100(this + 0x10);
  }
  *this = &PTR_LAB_00e2f638;
  if ((param_2 & 1) != 0) {
    piVar2 = (int *)FUN_009c8f80();
    (**(code **)(*piVar2 + 4))(this,0xd0);
  }
  return this;
}