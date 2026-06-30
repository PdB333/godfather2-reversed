// FUNC_NAME: MessageHandler::processMessage

void __thiscall MessageHandler::processMessage(int *pMsgType)
{
  char cTemp;

  // Check for message type A (global constant)
  if (*pMsgType == DAT_01206940) {
    FUN_00566c90(); // handleMessageTypeA
    return;
  }

  // Check for message type B (global constant)
  if (*pMsgType == DAT_01218050) {
    // If the int flag at +0x1c is zero and pre-check passes, skip further processing
    if (*(int *)(this + 0x1c) == 0) {
      cTemp = FUN_00566af0(); // preCheckForTypeB
      if (cTemp != '\0') {
        return;
      }
    }
    FUN_00566b70(); // handleMessageTypeB
    // If the char flag at +0x130 is set, perform additional action
    if (*(char *)(this + 0x130) != '\0') {
      FUN_004becf0(); // handleSpecialCondition
    }
  }
  return;
}