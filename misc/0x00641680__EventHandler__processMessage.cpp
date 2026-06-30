// FUNC_NAME: EventHandler::processMessage
int EventHandler::processMessage(void)
{
  int returnValue;
  int messageId = *(int *)(this + 0xc);
  void *dataPtr = *(void **)(this + 4);

  switch(messageId)
  {
  case 0x102: // Some event ID
    FUN_006415b0();
    return 1;
  case 0x103:
    FUN_0063db50();
    FUN_0063fc60();
    FUN_0063dc80(dataPtr);
    return 0;
  case 0x108:
    FUN_00640c60(dataPtr);
    return 0;
  case 0x109:
    FUN_006413f0(dataPtr);
    return 0;
  case 0x10a:
    FUN_00640ec0(dataPtr);
    return 0;
  case 0x10c:
    break; // fall through to default-like handling
  case 0x110:
    FUN_00640330(dataPtr);
    return 0;
  case 0x111:
    FUN_006414d0();
    return 1;
  case 0x115:
    FUN_0063fee0();
    return 0;
  default:
    FUN_00641470();
    return 0;
  }

  // For case 0x10c, and also default path for other cases that break
  FUN_0063db50();
  if ((messageId == 0x109) && (int result = FUN_0063dbf0(); result != 0)) {
    FUN_006410c0();
    return 0;
  }
  FUN_00641190();
  return 0;
}