// FUNC_NAME: SomeManager::shutdown
undefined4 __fastcall SomeManager::shutdown(int thisPtr)
{
  // +0x2f8: flag for resource A (e.g., music stream)
  if (*(char *)(thisPtr + 0x2f8) != '\0') {
    releaseResourceA(); // FUN_009bd900
    *(char *)(thisPtr + 0x2f8) = 0;
  }
  // +0x2f9: flag for resource B (e.g., SFX stream)
  if (*(char *)(thisPtr + 0x2f9) != '\0') {
    releaseResourceB(); // FUN_009bd940
    *(char *)(thisPtr + 0x2f9) = 0;
  }
  shutdownBase(); // FUN_009bd2f0
  return 0;
}