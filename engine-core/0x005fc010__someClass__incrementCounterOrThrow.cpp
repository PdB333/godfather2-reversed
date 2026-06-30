// FUNC_NAME: someClass::incrementCounterOrThrow
void someClass::incrementCounterOrThrow(void)
{
  // Check if the counter at offset +0x1c has reached the max value (0x3fffffff)
  if (*(int *)(unaff_ESI + 0x1c) == 0x3fffffff) {
    // Setup exception data for throwing "list<T> too long"
    local_28 = 0xf;
    local_2c = 0;
    local_3c = local_3c & 0xffffff00;
    FUN_0043f9f0("list<T> too long",0x10); // Likely exception constructor or message setup
    local_20 = "unknown";
    local_24 = &PTR_FUN_00da9810;          // Vtable or function table for exception
    local_4 = 0xf;
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    FUN_0043eeb0(local_40,0,0xffffffff);  // Another exception parameter setup
    local_24 = &PTR_FUN_00da9828;
    // Invoke a global function pointer if it exists (likely custom exception handler or runtime)
    if (DAT_0113d3a0 != (code *)0x0) {
      (*DAT_0113d3a0)(&local_24);
    }
    // Call the destructor or throw function via the vtable
    (*(code *)local_24[2])();
    // Throw the exception (std::_Throw wrapper)
    std::_Throw((exception *)&local_24);
    // Cleanup local data
    local_24 = &PTR_FUN_00da9810;
    if (0xf < local_4) {
      FUN_009c8eb0(local_18); // Likely deallocation function
    }
    local_8 = 0;
    local_18 = local_18 & 0xffffff00;
    local_4 = 0xf;
    local_24 = &PTR_LAB_00e31044;
    if (0xf < local_28) {
      FUN_009c8eb0(local_3c);
    }
  }
  // Increment the counter at offset +0x1c
  *(int *)(unaff_ESI + 0x1c) = *(int *)(unaff_ESI + 0x1c) + 1;
  return;
}