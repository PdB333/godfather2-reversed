// FUNC_NAME: SomeListClass::processAndCleanup
void __fastcall SomeListClass::processAndCleanup(int this)
{
  int *vtablePtr;
  undefined4 *nodePtr;
  
  for (nodePtr = *(undefined4 **)(this + 0x10); nodePtr != (undefined4 *)(this + 0x10);
      nodePtr = (undefined4 *)*nodePtr) {
    if ((nodePtr[2] != 0) && (vtablePtr = (int *)(nodePtr[2] + -0x48), vtablePtr != (int *)0x0)) {
      // Call virtual function at vtable offset 0x3c (likely a cleanup/destroy method)
      (**(code **)(*vtablePtr + 0x3c))(0);
    }
  }
  // Call global cleanup function
  FUN_0089caa0();
  return;
}