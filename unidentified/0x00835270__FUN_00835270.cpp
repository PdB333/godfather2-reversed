// FUNC_NAME: SomeClass::updateTransformOrSomething
void __fastcall SomeClass::updateTransformOrSomething(int this)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_18 [2];
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;

  if (*(int *)(this + 0x34) != 0) {
    uVar2 = 0;
    uVar3 = 0;
    uVar4 = 0;
    if (DAT_0112a53c != 0) {
      FUN_00826540(local_18);
      uVar2 = local_10;
      uVar3 = local_c;
      uVar4 = local_8;
    }
    puVar1 = (undefined4 *)(this + 0xb8);
    if (puVar1 != local_18) {
      *puVar1 = 0;
      *(undefined4 *)(this + 0xbc) = 0;
      *(undefined4 *)(this + 0xc0) = 0;
      *(undefined4 *)(this + 0xc4) = uVar2;
      *(undefined4 *)(this + 200) = uVar3;
      *(undefined4 *)(this + 0xcc) = uVar4;
    }
    FUN_00834380(puVar1);
  }
  return;
}