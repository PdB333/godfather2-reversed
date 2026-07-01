// FUNC_NAME: SomeClass::releaseOrDeletePointer
void __fastcall SomeClass::releaseOrDeletePointer(int *param_1)
{
  if (*param_1 != 0) {
    FUN_004daf90(param_1); // Likely a destructor or release function for the pointed-to object
    *param_1 = 0;          // Null out the pointer after releasing
  }
  return;
}