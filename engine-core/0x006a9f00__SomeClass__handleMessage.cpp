// FUNC_NAME: SomeClass::handleMessage
void __thiscall SomeClass::handleMessage(int thisPtr, int *messageData)
{
  int messageType;
  
  messageType = *messageData;
  if (messageType == DAT_012069c4) {
    FUN_006a9870();
    return;
  }
  if (messageType == DAT_0120e93c) {
    FUN_006a9510();
    FUN_004086d0(&DAT_0120e93c);
    return;
  }
  if (messageType != *(int *)(thisPtr + 0x14)) {
    if (messageType != *(int *)(thisPtr + 0x1c)) {
      if (messageType == *(int *)(thisPtr + 0x24)) {
        *(undefined4 *)(thisPtr + 0x80) = *(undefined4 *)messageData[1];
        goto LAB_006a9f57;
      }
      if (messageType != *(int *)(thisPtr + 0x2c)) {
        return;
      }
      *(undefined4 *)(thisPtr + 0x84) = *(undefined4 *)messageData[1];
    }
    FUN_006a96e0();
    return;
  }
LAB_006a9f57:
  FUN_006a9510();
  return;
}