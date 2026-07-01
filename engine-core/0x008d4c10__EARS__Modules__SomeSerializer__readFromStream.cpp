// FUNC_NAME: EARS::Modules::SomeSerializer::readFromStream
void __thiscall FUN_008d4c10(int this, undefined4 stream)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(stream);
  FUN_0043aff0(stream,0x4b59f28e);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x68) = *(undefined4 *)(iVar3 + 8);
      break;
    case 1:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar2);
      break;
    case 2:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x58,uVar2);
      break;
    case 3:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004d3d90(uVar2);
      break;
    case 4:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar3 + 8);
      break;
    case 5:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar3 + 8);
      break;
    case 6:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004d3d90(uVar2);
      break;
    case 7:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x94) = *(undefined4 *)(iVar3 + 8);
      break;
    case 8:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x98) = *(undefined4 *)(iVar3 + 8);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  if (DAT_0120e93c != 0) {
    FUN_00408900(this + 0x3c,&DAT_0120e93c,0x8000);
  }
  return;
}