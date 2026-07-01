// FUNC_NAME: SomeClass::createAndRegisterAction
void __thiscall FUN_008abea0(undefined4 thisPtr, int param_2, undefined4 param_3, undefined4 param_4, code *callback, undefined4 param_6, undefined4 param_7, undefined4 param_8)
{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_00481640(); // Check if game is active / not shutting down
  if (cVar1 != '\0') {
    iVar2 = FUN_009c8e50(0x58); // Allocate 0x58 bytes for new object
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_008abd20(thisPtr); // Constructor call for the object
    }
    FUN_004d3e20(&param_2); // Increment reference count on param_2 (smart pointer?)
    *(undefined4 *)(iVar2 + 0x48) = param_6; // +0x48: field1
    *(undefined4 *)(iVar2 + 0x4c) = param_7; // +0x4c: field2
    *(undefined4 *)(iVar2 + 0x50) = param_8; // +0x50: field3
    FUN_00481690(iVar2); // Register/activate the new object
  }
  if (param_2 != 0) {
    (*callback)(param_2); // Invoke callback with param_2
  }
  return;
}