// FUNC_NAME: SomeClass::releaseOrFreeResource
void __thiscall releaseOrFreeResource(undefined4 this, int *resourcePtr)
{
  if (resourcePtr != (int *)0x0) {
    // Call virtual function at vtable+0xc to get the resource handle/pointer
    resourcePtr = (int *)(**(code **)(*resourcePtr + 0xc))();
    // Delegate to helper function to actually free/release the resource
    FUN_0065d650(this, &resourcePtr);
  }
  return;
}