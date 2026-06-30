// FUNC_NAME: SomeClass::setTwoProperties
void __thiscall SomeClass::setTwoProperties(int thisPtr, undefined4 param2, undefined4 param3, undefined4 param4)
{
  FUN_00603bf0();
  FUN_004d3fe0(0x1f);
  FUN_004d4ad0(param4, &DAT_00e325c4, param2);
  FUN_004d4300(thisPtr + 0xb4); // +0xB4: first property value
  FUN_004d4b00(param4, &DAT_00e4086c, param3);
  FUN_004d4300(thisPtr + 0xc4); // +0xC4: second property value
  return;
}