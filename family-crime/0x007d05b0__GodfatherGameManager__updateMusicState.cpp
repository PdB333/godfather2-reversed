// FUNC_NAME: GodfatherGameManager::updateMusicState
void __fastcall GodfatherGameManager::updateMusicState(int *this)
{
  undefined4 musicState;
  
  // Check bit 1 of some flag at offset 0x8e0 in the object pointed to by this[0x16]
  if ((*(uint *)(this[0x16] + 0x8e0) >> 1 & 1) == 0) {
    musicState = 0xe5f463a8; // Music state: calm/exploration
  }
  else {
    musicState = 0x2bbac0fd; // Music state: combat
    if (0.0 < (float)this[0x1f]) {
      musicState = 0xa03d6a86; // Music state: intense combat/chase
    }
  }
  
  // Call virtual function at vtable+0x2c (likely setMusicState or playMusic)
  (**(code **)(*this + 0x2c))(musicState, 1, 0, 0, 0x3f800000, 0x3f800000);
  
  // Update audio system
  FUN_007f8980(); // AudioDataManager::update or similar
  FUN_007ac4f0(0); // StreamManager::update(0)
  FUN_007ac6f0(this[0x1f]); // StreamManager::setIntensity(this[0x1f])
  return;
}