// FUNC_NAME: SomeClass::constructor
undefined4 * SomeClass::constructor(undefined4 *this, int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  DAT_01223398 = this;
  *this = &PTR_FUN_00e36cb8; // vtable pointer
  uVar4 = 0;
  puVar3 = this;
  do {
    puVar3 = puVar3 + 1;
    puVar2 = (undefined4 *)FUN_009c8e50(0x1c); // allocate 0x1c bytes
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = (undefined4 *)0x0;
    }
    else {
      uVar1 = *(undefined4 *)(param_2 + uVar4 * 8); // read from param_2 array
      *puVar2 = &PTR_FUN_00e36cb4; // vtable pointer for inner object
      FUN_004cfc30(uVar1); // initialize inner object with uVar1
    }
    *puVar3 = puVar2; // store pointer in this+4, this+8
    uVar4 = uVar4 + 1;
  } while (uVar4 < 2); // loop twice
  return this;
}