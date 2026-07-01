// FUNC_NAME: SomeClass::checkAndNotifyOnlineStatus
void SomeClass::checkAndNotifyOnlineStatus(void *thisPtr, void (*callback)(bool))
{
  int isOnline;
  
  if (callback != (void (*)(bool))0x0) {
    isOnline = FUN_00adc2e0();
    (*callback)(isOnline == 0);
  }
  return;
}