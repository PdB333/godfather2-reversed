// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(undefined4 *this)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  *this = &PTR_FUN_00d805ec;
  this[2] = &PTR_LAB_00d805d0;
  this[0x11] = &PTR_LAB_00d805c0;
  this[0x14] = &PTR_LAB_00d805bc;
  this[0x16] = &PTR_LAB_00d805b8;
  this[0x16] = &PTR_LAB_00e32854;
  FUN_0046c640();
  *this = &PTR_FUN_00e32808;
  puVar2 = (undefined4 *)this[1];
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)puVar2[1];
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2 = puVar1;
  }
  return;
}