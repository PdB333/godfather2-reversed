// FUNC_NAME: SomeClass::checkTimerThreshold
bool __fastcall SomeClass::checkTimerThreshold(int this)
{
  // Compare global timer DAT_01205228 with this->timerThreshold at offset +0x7c
  return DAT_01205228 < *(float *)(this + 0x7c);
}