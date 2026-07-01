// FUNC_NAME: GodfatherGameManager::checkAndPlayAudio
void __fastcall GodfatherGameManager::checkAndPlayAudio(int this)
{
  undefined4 audioEvent;
  undefined4 param2;
  undefined1 param3;
  
  if ((*(byte *)(this + 0x30) & 2) != 0) {
    audioEvent = DAT_0112fc60;  // Global audio event ID
    param2 = 0;
    param3 = 0;
    FUN_00408a00(&audioEvent, 0);  // PlayAudioEvent(audioEvent*, 0)
  }
  return;
}