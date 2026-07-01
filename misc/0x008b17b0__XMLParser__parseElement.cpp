// FUNC_NAME: XMLParser::parseElement
void __thiscall XMLParser::parseElement(int this, undefined4 xmlData)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0046c710(xmlData);
  FUN_0043aff0(xmlData,0xa2165167);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if (iVar2 == 0) {
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar3);  // +0x50: attributeName
    }
    else if (iVar2 == 1) {
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_00408980(this + 0x58,uVar3);  // +0x58: attributeValue
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  return;
}