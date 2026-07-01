// FUNC_NAME: AudioManager::stopSound
void __fastcall AudioManager::stopSound(int this)
{
  undefined4 soundHandle;
  undefined4 stopFlags;
  
  stopFlags = 0x209;
  soundHandle = FUN_008fc140(*(int *)(this + 0x1c) + 0xec); // Get sound handle from +0x1c->+0xec
  FUN_008fd000(soundHandle, stopFlags); // Stop sound with flags
  FUN_008fcb40(0); // Release/cleanup
  return;
}