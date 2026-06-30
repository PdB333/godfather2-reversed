// FUNC_NAME: SomeClass::createSomeStruct
void SomeClass::createSomeStruct(undefined4 param1, undefined4 param2, undefined1 param3)
{
  // Call initialization function
  FUN_005c28c0();
  
  // Allocate memory for a struct via allocation function
  undefined4 *pStruct = (undefined4 *)FUN_005c2960();
  
  // Fill struct fields
  pStruct[1] = param1;  // +0x04: first parameter
  *pStruct = param2;    // +0x00: second parameter
  *(undefined1 *)(pStruct + 2) = param3;  // +0x08: third parameter (byte)
  
  return;
}