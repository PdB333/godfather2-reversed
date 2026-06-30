// FUNC_NAME: SomeClass::someMethod
void __fastcall SomeClass::someMethod(int param_1)
{
  int *in_EAX; // this pointer
  int local_c; // +0x4 offset from param_1
  int local_8; // param_1 itself
  int local_4; // computed index

  // Compute index: element at offset +0x8 (in_EAX[2]) + first element * 4
  local_4 = in_EAX[2] + *in_EAX * 4;

  // Set up pointers for the called function
  local_c = param_1 + 4; // points to param_1 + 4
  local_8 = param_1;     // points to param_1

  // Call helper function with this pointer and two pointer arguments
  FUN_005a3320(in_EAX, &local_8, &local_c);
}