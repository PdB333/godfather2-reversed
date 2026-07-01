// FUNC_NAME: GodfatherGameManager::onDifficultyChanged
undefined4 __thiscall GodfatherGameManager::onDifficultyChanged(int *this, int newDifficulty)
{
  int currentDifficulty;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  currentDifficulty = FUN_00466840(); // likely GameManager::getCurrentDifficulty()
  if (newDifficulty == currentDifficulty) {
    // Call virtual function at vtable+0x2c (likely onDifficultyApplied or similar)
    (**(code **)(*this + 0x2c))();
    local_c = DAT_011301b0; // some global data (maybe difficulty settings pointer)
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0); // likely applyDifficultySettings or resetDifficulty
  }
  return 0;
}