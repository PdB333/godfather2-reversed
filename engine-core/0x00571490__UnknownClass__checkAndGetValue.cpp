//FUNC_NAME: UnknownClass::checkAndGetValue
uint __thiscall UnknownClass::checkAndGetValue(void* thisPtr, int param1)
{
  uint result;

  // Guard: param1 must be non-null and thisPtr must not be -1 (invalid handle)
  if ((param1 != 0) && (thisPtr != (void*)-1)) {
    // Call two internal functions to compute the value
    FUN_00586970();   // likely some initialization or validation
    result = FUN_005787f0();  // returns the actual value
    return result;
  }
  // Fallback: return low byte of EAX masked (error or default)
  // in_EAX is the return value from previous operation (uninitialized in this path)
  return in_EAX & 0xffffff00;
}