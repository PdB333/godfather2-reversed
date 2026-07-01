// FUNC_NAME: AudioManager::activateSoundEffect
void __thiscall AudioManager::activateSoundEffect(int thisPtr, int soundId)
{
  uint index;
  int *entryArray;
  int entry;
  int state;
  float timeVal;

  index = 0;
  // +0x1a8: count of entries in the sound effect table
  if (*(uint *)(thisPtr + 0x1a8) != 0) {
    // +0x1a4: pointer to array of pointers to sound effect entries
    entryArray = *(int **)(thisPtr + 0x1a4);
    while (*(int *)(*entryArray + 8) != soundId) {  // +0x8: sound ID field
      index++;
      entryArray = entryArray + 1;
      if (*(uint *)(thisPtr + 0x1a8) <= index) {
        return;
      }
    }
    if (index != 0xFFFFFFFF) {  // always true if found, since index is uint
      entry = (*(int **)(thisPtr + 0x1a4))[index];
      state = *(int *)(entry + 4);  // +0x4: state field
      if ((state != 7) && (state != 5)) {  // 7 and 5 are likely "stopped" or "finished"
        FUN_008c8a80(1);  // probably setVolume or setPitch (parameter 1)
        timeVal = (float)FUN_008c82b0();  // returns current time or random offset
        if (*(int *)(entry + 4) != 7) {
          FUN_008c80d0(0);  // probably stop or pause (parameter 0)
          FUN_008c8a20(5, timeVal);  // probably play or resume (parameter 5, and time)
        }
      }
    }
  }
}