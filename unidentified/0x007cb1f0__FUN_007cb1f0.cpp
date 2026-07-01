// FUNC_NAME: SomeClass::releaseResource
void __fastcall SomeClass::releaseResource(int thisPtr)
{
  int *resourcePtr = (int *)(thisPtr + 0x7c); // +0x7C: resource handle/pointer
  if (*resourcePtr != 0) {
    FUN_004daf90(resourcePtr); // likely a resource manager release function
    *resourcePtr = 0;
  }
  return;
}