// FUNC_NAME: unknown::FUN_005b1830
void FUN_005b1830(void)
{
  int *esiPtr; // unaff_ESI
  undefined1 *stackVar5; // local_c
  undefined1 *stackVar4; // local_8
  int sum; // local_4

  // Sum the value at esiPtr[2] with the value at esiPtr[0]
  sum = esiPtr[2] + *esiPtr;
  // Set up stack variables for a function call
  stackVar5 = &stack0x00000005;
  stackVar4 = &stack0x00000004;
  // Call a helper function with pointers to stack variables
  FUN_005aba20(&stackVar4, &stackVar5);
  return;
}