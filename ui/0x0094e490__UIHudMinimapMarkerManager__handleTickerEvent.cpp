// FUNC_NAME: UIHudMinimapMarkerManager::handleTickerEvent
void __thiscall UIHudMinimapMarkerManager::handleTickerEvent(int this, int param_2, undefined4 param_3, int param_4, undefined4 param_5, int param_6, int param_7, undefined4 param_8)
{
  if (param_2 == param_4) {
    FUN_0094dfa0(param_3, param_6); // likely showTickerWithTwoParams
  }
  else if (param_6 == param_7) {
    FUN_0094df10(param_3, param_5, param_6); // likely showTickerWithThreeParams
  }
  else {
    FUN_0094de70(param_3, param_6, param_8, param_5, param_7); // likely showTickerWithFiveParams
  }
  *(undefined4 *)(this + 0x50) = 0; // +0x50: tickerTimer or tickerState
  FUN_005a04a0("ShowTicker", 0, &DAT_00d8b7d4, 0); // debug/log call
  FUN_005c0260(this + 0x10, &LAB_0094e300, 1); // +0x10: some state machine or animation controller
  return;
}