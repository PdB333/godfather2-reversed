// FUNC_NAME: SomeClass::removePlayerFromTeamSlots

void __thiscall removePlayerFromTeamSlots(int this, int param_2, int param_3)
{
  int i;
  int *slotPtr;
  
  if (param_3 == 0) {
    i = 0;
    slotPtr = (int *)(this + 0x104); // +0x104: team member slots array (8 slots)
    while (*slotPtr != param_2) {
      i = i + 1;
      slotPtr = slotPtr + 1;
      if (7 < i) {
        return;
      }
    }
    *(undefined4 *)(this + 0x104 + i * 4) = 0; // clear slot if match found
  }
  return;
}