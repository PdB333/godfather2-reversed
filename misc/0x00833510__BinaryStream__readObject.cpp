// FUNC_NAME: BinaryStream::readObject
void __thiscall BinaryStream::readObject(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0043aff0(param_2,0x20162d3e);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x10) = *(undefined4 *)(iVar3 + 8);
      break;
    case 1:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x14) = *(undefined4 *)(iVar3 + 8);
      break;
    case 2:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x18) = *(undefined4 *)(iVar3 + 8);
      break;
    case 3:
      iVar3 = this + 0x2c;
      goto LAB_0083358f;
    case 4:
      iVar3 = this + 0x3c;
LAB_0083358f:
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}