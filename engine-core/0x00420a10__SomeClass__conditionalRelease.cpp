// FUNC_NAME: SomeClass::conditionalRelease
void __thiscall SomeClass::conditionalRelease(int *ptrToResource) // ptrToResource points to a resource handle; if non-zero, release it
{
  if (*ptrToResource != 0) {
    // Call the actual release function (FUN_00407e60) on this object and the resource pointer
    FUN_00407e60(this, ptrToResource);
  }
  // If already zero, nothing to do
  return;
}