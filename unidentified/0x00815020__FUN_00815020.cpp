// FUNC_NAME: SomeClass::incrementAndSetParams
undefined4 __thiscall SomeClass::incrementAndSetParams(int this, undefined4 param2, undefined4 param3)
{
  // +0x14: some counter/ID field, initialized to -1 meaning "not set"
  if (*(int *)(this + 0x14) == -1) {
    *(undefined4 *)(this + 0x14) = 1;  // First call: set to 1
  }
  else {
    *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;  // Subsequent calls: increment
  }
  // +0x94 and +0x98: two parameter storage fields
  *(undefined4 *)(this + 0x94) = param2;
  *(undefined4 *)(this + 0x98) = param3;
  return *(undefined4 *)(this + 0x14);  // Return the new counter value
}