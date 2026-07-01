// FUNC_NAME: SomeManager::createOrGetObject
void __thiscall SomeManager::createOrGetObject(int this, int param2)
{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_00481660(); // Likely checks if manager is initialized or active
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x40); // Allocate memory of size 0x40 (64 bytes)
    if (iVar2 != 0) {
      iVar2 = FUN_008aa600(this); // Construct or initialize object at allocated memory
      *(int *)(iVar2 + 0x38) = param2; // Store param2 at offset +0x38
      FUN_00481690(iVar2); // Register or add object to manager
      return;
    }
    _DAT_00000038 = param2; // Fallback: store param2 in global (likely error case)
    FUN_00481690(0); // Register null object (error handling)
  }
  return;
}