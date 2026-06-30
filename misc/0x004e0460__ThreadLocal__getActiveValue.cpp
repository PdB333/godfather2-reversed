// FUNC_NAME: ThreadLocal::getActiveValue
int ThreadLocal::getActiveValue() {
  // Check if this thread-local storage has any non-zero fields (0x00, 0x04, 0x08, 0x0C)
  if ((field_0 != 0) || (field_4 != 0) || (field_8 != 0) || (field_C != 0)) {
    // Access the global singleton from FUN_004e0d30
    int* globalPtr = (int*)FUN_004e0d30();
    if ((globalPtr != nullptr) && (*globalPtr != 0)) {
      return *globalPtr;
    }
  }
  return 0;
}