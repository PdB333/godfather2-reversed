// FUNC_NAME: SomeClass::initSomeStruct
void __fastcall SomeClass::initSomeStruct(undefined4 *param_1)
{
  *param_1 = 2;          // +0x00: field1 = 2
  param_1[1] = 0;        // +0x04: field2 = 0
  param_1[2] = 3;        // +0x08: field3 = 3
  param_1[3] = 0;        // +0x0C: field4 = 0
  return;
}