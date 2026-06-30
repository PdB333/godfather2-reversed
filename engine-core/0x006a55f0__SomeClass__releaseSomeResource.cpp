// FUNC_NAME: SomeClass::releaseSomeResource
void __thiscall releaseSomeResource(int thisPtr, int *resourcePtr)
{
  int *storedResource = (int *)(thisPtr + 0x694);
  
  if ((*resourcePtr == *storedResource) && (*storedResource != 0)) {
    FUN_004daf90(storedResource); // likely a release/free function
    *storedResource = 0;
  }
  return;
}