// FUNC_NAME: SomeClass::findTimeSinceEvent
float __thiscall findTimeSinceEvent(int this, int eventType)
{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(this + 0x11c) + -1; // event count - 1
  if (-1 < iVar1) {
    piVar2 = (int *)(this + 0x5c + iVar1 * 0xc); // pointer to last event entry (each 12 bytes)
    do {
      if (*piVar2 == eventType) {
        return (float)DAT_01205228 - (float)(float)piVar2[1]; // currentTime - eventTime
      }
      iVar1 = iVar1 + -1;
      piVar2 = piVar2 + -3; // move to previous event entry (3 ints back = 12 bytes)
    } while (-1 < iVar1);
  }
  return (float)DAT_00d5f6f0; // default time value if event not found
}