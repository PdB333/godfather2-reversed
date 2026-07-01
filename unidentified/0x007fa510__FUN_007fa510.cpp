// FUNC_NAME: SomeClass::releaseOrDelete
void __fastcall SomeClass::releaseOrDelete(int *param_1)
{
  // Check if the pointer is non-null
  if (*param_1 != 0) {
    // Call the release/deallocation function (likely a destructor or refcount decrement)
    FUN_004daf90(param_1);
    // Null out the pointer after release
    *param_1 = 0;
  }
  return;
}