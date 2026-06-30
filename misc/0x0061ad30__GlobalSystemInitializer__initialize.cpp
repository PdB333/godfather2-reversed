// FUNC_NAME: GlobalSystemInitializer::initialize
void GlobalSystemInitializer::initialize(void)
{
  void *firstBuffer;
  int secondBufferHandle;

  // Copy a global state flag from another location
  s_globalStateFlag = s_previousStateFlag;

  // Allocate a buffer of 0x404 bytes (1028 bytes) for a structure/array
  firstBuffer = (void *)FUN_009c8e50(0x404);
  if (firstBuffer == (void *)0x0) {
    s_firstBufferPtr = (void *)0x0;
  }
  else {
    // Set last DWORD at offset 0x400 to 0 (maybe capacity or sentinel)
    *(undefined4 *)((int)firstBuffer + 0x400) = 0;
    // Zero out the first 0x400 bytes (1024 bytes)
    _memset(firstBuffer, 0, 0x400);
    s_firstBufferPtr = firstBuffer;
  }

  // Allocate a second buffer of 0x81C bytes (2076 bytes) for another object
  secondBufferHandle = FUN_009c8e50(0x81c);
  if (secondBufferHandle != 0) {
    // Initialize the second object and store handle
    s_secondBufferHandle = FUN_0061ac90();
    // Perform common post-initialization
    FUN_00610c40();
    return;
  }
  s_secondBufferHandle = 0;
  FUN_00610c40();
  return;
}