// FUNC_NAME: PlayerF2FSM::handleEvent
void __thiscall PlayerF2FSM::handleEvent(int thisPtr, int eventData)
{
  uint eventFlags;
  
  eventFlags = *(uint *)(eventData + 0x10);
  *(uint *)(thisPtr + 0x8c) = eventFlags;
  if ((eventFlags >> 1 & 1) != 0) {
    FUN_008e8e30(); // likely enterF2FState or similar
    FUN_00791e70(thisPtr + 0x50); // likely startF2FAnimation or transition
  }
  return;
}