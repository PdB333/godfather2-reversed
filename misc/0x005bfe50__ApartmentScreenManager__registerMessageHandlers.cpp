// FUNC_NAME: ApartmentScreenManager::registerMessageHandlers
void ApartmentScreenManager::registerMessageHandlers(void)
{
  // Only register on first call (singleton-style initialization)
  if (s_registrationCount == 0) {
    uint32_t msgId = getMessageId("iMsgAptScreenShown");
    registerMessageHandler(&s_shownHandler, msgId);
    msgId = getMessageId("iMsgAptScreenHidden");
    registerMessageHandler(&s_hiddenHandler, msgId);
  }
  ++s_registrationCount;
}