// FUNC_NAME: SomeClass::initializeSegment
void __thiscall SomeClass::initializeSegment(uint param_2, int param_3, undefined4 param_4)
{
  // This function appears to set up a memory segment or resource block.
  // param_1: this pointer (SomeClass instance)
  // param_2: likely a size or flags (shifted right 2 bits)
  // param_3: pointer to a structure (e.g., a buffer descriptor)
  // param_4: possibly an identifier or context

  // Call into another init function with zero arguments and the passed param_4, this, and EAX
  FUN_00556ab0(0, 0, param_4, this, in_EAX); // in_EAX is undefined; likely some register artifact

  // Store a combined value at offset +0x2c of param_3's structure
  // The value is (param_2 >> 2) | 0xC0000000
  *(uint *)(param_3 + 0x2c) = (param_2 >> 2) | 0xC0000000;

  // Call unknown engine functions
  FUN_0043b490(); // Possibly a debug or assert check
  FUN_009f01f0(0x2001, param_4, 0); // Logging or system call with code 0x2001
  return;
}