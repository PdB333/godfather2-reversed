// FUNC_NAME: AudioDataManager::loadSoundBank
void __thiscall AudioDataManager::loadSoundBank(int this, undefined4 bankName)
{
  undefined4 soundId;
  undefined1 *bankNamePtr;
  
  FUN_004d3e20(bankName); // Possibly a string copy or validation
  bankNamePtr = *(undefined1 **)(this + 0x14);
  if (bankNamePtr == (undefined1 *)0x0) {
    bankNamePtr = &DAT_0120546e; // Default bank name fallback
  }
  soundId = FUN_004dafd0(bankNamePtr); // Load sound bank and get ID
  *(undefined4 *)(this + 0x10) = soundId; // Store sound bank ID at +0x10
  return;
}