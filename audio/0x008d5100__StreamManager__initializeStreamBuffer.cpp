// FUNC_NAME: StreamManager::initializeStreamBuffer
void __fastcall StreamManager::initializeStreamBuffer(int thisPtr)
{
  if (*(char *)(thisPtr + 0x81) == '\0') {
    if (DAT_0112f9d0 != 0) {
      FUN_00408900(thisPtr + 0x4c, &DAT_0112f9d0, 0x8000);
    }
    *(undefined1 *)(thisPtr + 0x81) = 1;
  }
  return;
}