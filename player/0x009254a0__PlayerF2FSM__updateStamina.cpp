// FUNC_NAME: PlayerF2FSM::updateStamina
void __fastcall PlayerF2FSM::updateStamina(PlayerF2FSM* thisPtr)
{
  float fVar1;
  
  // Decrease stamina by the drain rate (stored at +0xAC)
  fVar1 = *(float *)((int)thisPtr + 0x1398) - *(float *)((int)thisPtr + 0xAC);
  *(float *)((int)thisPtr + 0x1398) = fVar1;
  
  // Clamp stamina to minimum value (stored at +0xA8)
  if (fVar1 < *(float *)((int)thisPtr + 0xA8)) {
    *(float *)((int)thisPtr + 0x1398) = *(float *)((int)thisPtr + 0xA8);
  }
  return;
}