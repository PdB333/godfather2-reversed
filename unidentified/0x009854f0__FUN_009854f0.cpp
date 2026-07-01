// FUNC_NAME: SomeClass::releaseOrDelete
void FUN_009854f0(void* thisPtr, int objectPtr)
{
  if (objectPtr != 0) {
    FUN_009823b0();  // likely decrementRefCount or release
    FUN_009c8eb0(objectPtr);  // likely delete or free
  }
  return;
}