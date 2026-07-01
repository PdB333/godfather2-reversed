// FUNC_NAME: SomeManager::createSomeObject
void __fastcall SomeManager::createSomeObject(undefined4 param_1)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  cVar1 = FUN_00481640(); // likely some condition check (e.g., isInitialized)
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x38); // allocate memory of size 0x38 (56 bytes)
    if (iVar2 != 0) {
      uVar3 = FUN_008dbc50(param_1); // construct object at allocated memory
      FUN_00481690(uVar3); // register/activate the object
      return;
    }
    FUN_00481690(0); // register null (failure)
  }
  return;
}