// FUNC_NAME: SomeClass::loadSpecialValueOrSomething
void __thiscall FUN_004cfa60(int this, undefined4 param_2)
{
  int *piVar1;
  bool bVar2;
  char local_64;       // actually might be a small struct/flag
  int local_58;        // might be a pointer or count
  int local_54;        // might be a pointer or count
  int local_50 [18];   // array of 18 ints (72 bytes)
  int *local_8;        // array of 8 ints? Actually local_8 is a pointer
  // Note: local_64, local_58, local_54, local_50, local_8 are local variables
  // but the stack frame is messy. The actual usage suggests local_64 is a discriminator
  // and either local_8 or local_50 is used, with local_58 and local_54 as size/count.

  // Calls: FUN_0043aff0(param_2, 0xe794215b); // probably some hash/deserialization
  // Calls: FUN_0043af00(0); // maybe a reader advance or next token?

  // The logic: if local_64 == 0, treat local_8 as an array and check if local_8[0] == 0.
  // Otherwise, treat local_58 and local_54 as a range (or count) and check if they are equal.
  if (local_64 == '\0') {
    bVar2 = *local_8 == 0;   // first element of array pointed by local_8 is zero
  } else {
    bVar2 = local_58 == local_54;  // two counters/pointers equal
  }

  // If the condition is false (i.e., not empty or not at end), then extract a value
  if (!bVar2) {
    piVar1 = local_50;   // default: use local_50 array
    if (local_64 == '\0') {
      piVar1 = local_8;   // actually use local_8 pointer
    }
    // Write the third element (index 2) of the selected array as a byte to this+0x8c
    *(char *)(this + 0x8c) = (char)piVar1[2];
  }
  return;
}