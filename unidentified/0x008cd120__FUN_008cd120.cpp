// FUNC_NAME: SomeClass::constructor
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  int iVar1;
  
  this[1] = param_2;
  this[2] = param_3;
  this[3] = &PTR_FUN_00e2f19c; // vtable or function pointer
  this[4] = 1; // some flag or count
  this[5] = 0; // some counter or pointer
  *this = &PTR_FUN_00d7c808; // vtable pointer
  this[3] = &PTR_LAB_00d7c7f4; // another vtable or function pointer
  this[6] = 0; // some state
  this[7] = param_4; // stored parameter
  iVar1 = FUN_004a37d0(); // likely getSingleton or getManager
  if (((*(int *)(iVar1 + 0x1c) != 0) && (*(int *)(iVar1 + 8) == 0x1961bed)) &&
     (iVar1 = *(int *)(*(int *)(iVar1 + 0x1c) + 0x14), iVar1 != 0)) {
    FUN_008cd070(iVar1); // likely register or initialize something
  }
  return this;
}