// FUNC_NAME: SomeClass::setStateOrMode
void __fastcall SomeClass::setStateOrMode(int this)
{
  *(uint8_t *)(this + 0x14) = 0x13;  // +0x14: state/mode byte, set to 0x13 (19)
  *(int32_t *)(this + 0x18) = 0;     // +0x18: some counter/timer, reset to 0
  DAT_00f17964 = 0x11;               // global variable set to 0x11 (17)
  if (*(int32_t *)(this + 0x10) != 3) {  // +0x10: some status/phase
    FUN_00444930(1);                 // likely a function to set or reset something with arg=1
    *(int32_t *)(this + 0x10) = 1;   // +0x10: set to 1
  }
  return;
}