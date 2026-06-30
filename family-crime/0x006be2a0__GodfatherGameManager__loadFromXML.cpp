// FUNC_NAME: GodfatherGameManager::loadFromXML
void __thiscall GodfatherGameManager::loadFromXML(int this, undefined4 xmlNode)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0046c710(xmlNode);
  FUN_0043aff0(xmlNode,0x500b9169);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x50) = *(undefined4 *)(iVar3 + 8);
      break;
    case 1:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0x54) = *(undefined4 *)(iVar3 + 8);
      break;
    case 2:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x58,uVar2);
      break;
    case 3:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x60,uVar2);
      break;
    case 4:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0x68,uVar2);
      break;
    case 5:
      iVar3 = FUN_0043b210();
      *(uint *)(this + 0x70) = *(uint *)(this + 0x70) | *(uint *)(iVar3 + 8);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  if ((*(byte *)(this + 0x70) & 1) != 0) {
    FUN_00408680(&DAT_0120e93c);
  }
  if ((*(uint *)(this + 0x70) >> 1 & 1) != 0) {
    FUN_00408680(&DAT_0112a620);
  }
  return;
}