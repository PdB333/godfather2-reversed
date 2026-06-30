// FUNC_NAME: AudioDataManager::loadAudioBank
void AudioDataManager::loadAudioBank(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_009c8e50(0xc);
  if (iVar1 == 0) {
    DAT_01129bc4 = 0;
  }
  else {
    DAT_01129bc4 = FUN_00690860();
  }
  uVar2 = FUN_00691a70();
  if (DAT_01206a08 != 0) {
    FUN_00408900(uVar2,&DAT_01206a08,0x8000);
  }
  return;
}