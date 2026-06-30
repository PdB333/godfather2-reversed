// FUNC_NAME: UnknownClass::dispatchTimerEvent
void __fastcall dispatchTimerEvent(int *this, undefined4 param_2, undefined4 param_3)
{
  struct TimerEvent_R5 {
    undefined4 unk0;      // +0x00
    undefined4 callAddr;  // +0x04
    undefined8 unk8;      // +0x08
    undefined8 unk10;     // +0x10
  } event;                // local_18 size: 0x18

  event.unk0 = param_2;
  event.callAddr = 0x568a70;     // callback at 0x568a70
  event.unk8 = 0;                // timer ID or flags (zero)
  event.unk10 = 0;               // user data or context (zero)

  // Dispatch to virtual timer handler at vtable+0x08 with:
  // - event structure pointer
  // - flags = 0
  // - delay = 10000 ms (10 seconds)
  (*(code **)(*this + 8))(param_3, &event, 0, 10000);
}