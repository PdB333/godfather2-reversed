// FUNC_NAME: AudioDataManager::initAudioData
void AudioDataManager::initAudioData(void)
{
  undefined4 uVar1;
  undefined2 *in_EAX;
  undefined4 *puVar2;
  int iVar3;
  
  uVar1 = DAT_00e2b1a4;
  *in_EAX = 0;
  in_EAX[1] = 0;
  *(undefined4 *)(in_EAX + 2) = uVar1;
  *(undefined4 *)(in_EAX + 4) = 0;
  *(undefined4 *)(in_EAX + 6) = 0;
  *(undefined4 *)(in_EAX + 8) = uVar1;
  *(undefined4 *)(in_EAX + 10) = 0;
  *(undefined4 *)(in_EAX + 0xc) = 0;
  *(undefined4 *)(in_EAX + 0x56) = 0xffffffff;
  *(undefined8 *)(in_EAX + 0x58) = 0;
  *(undefined1 *)(in_EAX + 0x5c) = 0;
  *(undefined4 *)(in_EAX + 0xe) = uVar1;
  *(undefined4 *)(in_EAX + 0x54) = 0;
  puVar2 = (undefined4 *)(in_EAX + 0x12);
  iVar3 = 0x10;
  do {
    puVar2[-1] = uVar1;
    *puVar2 = 0;
    puVar2 = puVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(undefined4 *)(in_EAX + 0x50) = 0;
  *(undefined4 *)(in_EAX + 0x52) = 0;
  *(undefined4 *)(in_EAX + 0x78) = 0;
  *(undefined4 *)(in_EAX + 0x76) = 96000;
  return;
}