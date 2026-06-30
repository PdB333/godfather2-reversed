// FUNC_NAME: StreamManager::createStreamBuffer
int StreamManager::createStreamBuffer(int param1, int param2, int param3)
{
  int result;
  void *buffer;
  struct {
    int field0; // +0x00
    int field4; // +0x04
    int field8; // +0x08
  } localStruct;

  buffer = _calloc(4, 0x40);
  if (buffer != (void *)0x0) {
    localStruct.field0 = 0;
    localStruct.field4 = 0x40;
    localStruct.field8 = 0;
    result = FUN_0066a780(param1, param2);
    if (result == 0) {
      result = FUN_00668850(&localStruct, param3);
    }
    FUN_00665b40();
    return result;
  }
  return -2;
}