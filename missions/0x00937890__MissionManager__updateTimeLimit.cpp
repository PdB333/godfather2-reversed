// FUNC_NAME: MissionManager::updateTimeLimit
void __fastcall MissionManager::updateTimeLimit(int this)
{
  int timeLimit;
  int local_c;
  int dummy;

  // Apply time penalty or bonus
  FUN_008c74d0(*(int*)(*(int*)(this + 0x6c) + 0x40));
  timeLimit = *(int*)(this + 0x58);
  if (timeLimit < 1) {
    if (timeLimit < 0) {
      // Negative time: penalty (reduce remaining time)
      FUN_008be590(*(int*)(*(int*)(this + 0x6c) + 0x38), -timeLimit);
      local_c = DAT_01130268; // Some global identifier
    }
    else {
      // Zero time: no change
      local_c = DAT_01130400; // Some global identifier
    }
  }
  else {
    // Positive time: bonus (add remaining time)
    FUN_008c0b10(*(int*)(*(int*)(this + 0x6c) + 0x38), timeLimit, 1);
    local_c = DAT_01130268; // Some global identifier
  }
  dummy = 0;
  ((void (*)(int*,int))0x00408a00)(&local_c, 0); // Probably log/dump function
}