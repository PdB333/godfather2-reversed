// FUNC_NAME: SomeClass::destructor
void __fastcall SomeClass::destructor(undefined4 *this)
{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  
  piVar1 = this + 2; // +0x08
  *this = &PTR_FUN_00e407c4; // vtable pointer
  FUN_005f5ce0(); // likely base destructor
  piVar6 = this + 5; // +0x14
  FUN_005f5ce0(); // another base destructor
  uVar8 = DAT_01223520; // global data
  puVar2 = (undefined4 *)this[0xc]; // +0x30
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = 0;
    FUN_004abf50(puVar2); // operator delete
  }
  this[0xc] = 0; // +0x30
  uVar8 = FUN_005f7fa0(uVar8,this[9],this + 10); // +0x24, +0x28
  this[9] = uVar8; // +0x24
  iVar3 = *piVar6; // +0x14
  if (iVar3 != 0) {
    piVar4 = *(int **)(iVar3 + 4);
    if (piVar4 == piVar6) {
      *(undefined4 *)(iVar3 + 4) = this[6]; // +0x18
    }
    else {
      piVar5 = (int *)piVar4[1];
      while (piVar5 != piVar6) {
        piVar4 = (int *)piVar4[1];
        piVar5 = (int *)piVar4[1];
      }
      piVar4[1] = this[6]; // +0x18
    }
  }
  iVar3 = *piVar1; // +0x08
  if (iVar3 != 0) {
    piVar6 = *(int **)(iVar3 + 4);
    if (piVar6 == piVar1) {
      *(undefined4 *)(iVar3 + 4) = this[3]; // +0x0C
    }
    else {
      piVar4 = (int *)piVar6[1];
      while (piVar4 != piVar1) {
        piVar6 = (int *)piVar6[1];
        piVar4 = (int *)piVar6[1];
      }
      piVar6[1] = this[3]; // +0x0C
    }
  }
  *this = &PTR_FUN_00e32808; // vtable pointer (derived class)
  puVar2 = (undefined4 *)this[1]; // +0x04
  while (puVar2 != (undefined4 *)0x0) {
    puVar7 = (undefined4 *)puVar2[1];
    puVar2[1] = 0;
    *puVar2 = 0;
    puVar2 = puVar7;
  }
  return;
}