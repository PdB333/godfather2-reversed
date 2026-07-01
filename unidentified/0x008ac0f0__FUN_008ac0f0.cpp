// FUNC_NAME: SomeClass::createSomeObject
void __thiscall SomeClass::createSomeObject(undefined4 this, int param_2, undefined4 param_3, undefined4 param_4, code *callback, undefined4 param_6, undefined4 param_7, undefined4 param_8)
{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_00481660(); // Check if some condition is met (e.g., game state valid)
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x58); // Allocate memory of size 0x58 (88 bytes)
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_008abf70(param_1); // Initialize object at allocated memory
    }
    FUN_004d3e20(&param_2); // Process or transform param_2 (e.g., reference counting)
    *(undefined4 *)(iVar2 + 0x48) = param_6; // +0x48: field6
    *(undefined4 *)(iVar2 + 0x4c) = param_7; // +0x4c: field7
    *(undefined4 *)(iVar2 + 0x50) = param_8; // +0x50: field8
    FUN_00481690(iVar2); // Register or finalize the object
  }
  if (param_2 != 0) {
    (*param_5)(param_2); // Callback with param_2 as argument
  }
  return;
}