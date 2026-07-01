// FUNC_NAME: GodfatherGameManager::updateAmbientAnimationMode
void __thiscall GodfatherGameManager::updateAmbientAnimationMode(GodfatherGameManager *this)
{
  int iVar1;
  
  iVar1 = g_ambientAnimationMode; // Global ambient animation mode state
  if (iVar1 != *(int *)((uint8_t *)this + 0x2e10)) { // +0x2e10: m_currentAmbientAnimMode
    *(int *)((uint8_t *)this + 0x2e10) = iVar1;
    FUN_00894c90(0xf2696411); // Fire event: 0xf2696411 = kEventAmbientAnimModeChanged
  }
  return;
}