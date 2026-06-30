// FUNC_NAME: GodfatherGameManager::handlePlaySoundBuffer
void GodfatherGameManager::handlePlaySoundBuffer(void)

{
  char soundIndex2;
  int *soundManager;
  int soundHandle;
  int soundIndex1;
  
  soundIndex2 = *(char *)(DAT_012233b4 + 0x565);
  if (((*(char *)(DAT_012233b4 + 0x564) != '\x12') && (DAT_00e50698 != -1)) &&
     ((&DAT_00e50658)[DAT_00e50698] != 0)) {
    soundHandle = 0;
    for (; (DAT_00e50698 != -1 && (soundManager = &DAT_00e50658 + DAT_00e50698, *soundManager != 0));
        DAT_00e50698 = DAT_00e50698 + -1) {
      soundHandle = *soundManager;
    }
    soundManager = (int *)FUN_00411070(*(undefined1 *)(DAT_012233b4 + 0x564));
    (**(code **)(*soundManager + 8))(soundHandle);
  }
  if (((soundIndex2 != '\x12') && (DAT_00e50650 != -1)) && ((&DAT_00e50610)[DAT_00e50650] != 0)) {
    soundHandle = 0;
    for (; (DAT_00e50650 != -1 && (soundManager = &DAT_00e50610 + DAT_00e50650, *soundManager != 0));
        DAT_00e50650 = DAT_00e50650 + -1) {
      soundHandle = *soundManager;
    }
    soundManager = (int *)FUN_00411070(*(undefined1 *)(DAT_012233b4 + 0x565));
    (**(code **)(*soundManager + 8))(soundHandle);
  }
  return;
}