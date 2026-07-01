// FUNC_NAME: SomeClass::deserializeFromStream
void __thiscall SomeClass::deserializeFromStream(int this, undefined4 stream)
{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  
  FUN_0043aff0(stream,0xf7a92bbe);
  cVar2 = FUN_0043b120();
  while (cVar2 == '\0') {
    FUN_0043b210();
    uVar3 = FUN_0043ab70();
    switch(uVar3) {
    case 0:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004d3d90(uVar3);
      break;
    case 1:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x9c) = *(undefined4 *)(iVar4 + 8);
      break;
    case 2:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004d3d90(uVar3);
      break;
    case 3:
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004d3d90(uVar3);
      break;
    case 4:
      iVar4 = FUN_0043b210();
      *(undefined4 *)(this + 0x98) = *(undefined4 *)(iVar4 + 8);
      break;
    case 5:
      iVar4 = this + 0x60;
      FUN_0043b210(iVar4);
      FUN_0043ad10(iVar4);
      break;
    case 6:
      iVar4 = this + 0x70;
      FUN_0043b210(iVar4);
      FUN_0043ad10(iVar4);
      break;
    case 7:
      iVar4 = FUN_0043b210();
      *(bool *)(this + 0xc4) = *(int *)(iVar4 + 8) != 0;
      break;
    case 8:
      iVar4 = FUN_0043b210();
      uVar1 = *(uint *)(iVar4 + 8);
      *(uint *)(this + 0xc0) = uVar1;
      if (0x708 < uVar1) {
        *(undefined4 *)(this + 0xc0) = 0x708;
      }
    }
    FUN_0043b1a0();
    cVar2 = FUN_0043b120();
  }
  return;
}