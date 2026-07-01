// FUNC_NAME: GodfatherGameManager::loadGameSettings
void __thiscall GodfatherGameManager::loadGameSettings(int this, undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0xc4751187);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar2);  // +0x50: some string setting
      break;
    case 1:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x58) = *(undefined4 *)(iVar3 + 8);  // +0x58: int setting
      break;
    case 2:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x5c) = *(undefined4 *)(iVar3 + 8);  // +0x5c: int setting
      break;
    case 3:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x6c) = *(undefined4 *)(iVar3 + 8);  // +0x6c: int setting
      break;
    case 4:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x60) = *(undefined4 *)(iVar3 + 8);  // +0x60: int setting
      break;
    case 5:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 100) = *(undefined4 *)(iVar3 + 8);  // +0x64: int setting
      break;
    case 6:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x68) = *(undefined4 *)(iVar3 + 8);  // +0x68: int setting
      break;
    case 7:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x70) = *(undefined4 *)(iVar3 + 8);  // +0x70: int setting
      break;
    case 8:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x74) = *(undefined4 *)(iVar3 + 8);  // +0x74: int setting
      break;
    case 9:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x78) = *(undefined4 *)(iVar3 + 8);  // +0x78: int setting
      break;
    case 10:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x80) = *(undefined4 *)(iVar3 + 8);  // +0x80: int setting
      break;
    case 0xb:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x84) = *(undefined4 *)(iVar3 + 8);  // +0x84: int setting
      break;
    case 0xc:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x7c) = *(undefined4 *)(iVar3 + 8);  // +0x7c: int setting
      break;
    case 0xd:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x88) = *(undefined4 *)(iVar3 + 8);  // +0x88: int setting
      break;
    case 0xe:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x8c) = *(undefined4 *)(iVar3 + 8);  // +0x8c: int setting
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}