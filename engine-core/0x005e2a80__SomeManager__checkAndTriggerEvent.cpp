// FUNC_NAME: SomeManager::checkAndTriggerEvent
void SomeManager::checkAndTriggerEvent(uint param_1, uint param_2, uint param_3)
{
  // +0x1744: flag indicating if event trigger is enabled
  if (*(char *)(DAT_0122350c + 0x1744) != '\0') {
    // 0x32 = 50, likely a timer or priority value
    FUN_005e25f0(DAT_0122350c, param_1, param_2, param_3, 0x32);
  }
  return;
}