// FUNC_NAME: Family::constructor
undefined4 __fastcall Family::constructor(undefined4 this)
{
  int *piVar1;
  
  FUN_0041ea70(); // base class constructor
  FUN_0041ea40(0,0x340); // memset(this+0x?, 0, 0x340) likely initializes member data to zero
  piVar1 = (int *)(DAT_01206880 + 0x14); // get vtable pointer location
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_00e500cc; // set vtable to Family vtable
  *piVar1 = *piVar1 + 4; // advance pointer? Possibly related to ref counting or vtable table
  return this;
}