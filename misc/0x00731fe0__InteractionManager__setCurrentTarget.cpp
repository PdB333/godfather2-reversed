// FUNC_NAME: InteractionManager::setCurrentTarget
void __thiscall InteractionManager::setCurrentTarget(InteractionManager *this, int newTarget)
{
  int oldTarget;
  int gameMode;

  oldTarget = this->m_pCurrentTarget; // +0x2134
  if (oldTarget != newTarget) {
    // Check if callback registration is enabled (bit 8 of m_flags)
    if (((this->m_flags >> 8 & 1) != 0) && (oldTarget != 0)) {
      // Unregister old target listener
      registerTargetListener(oldTarget, 0); // 0x6b0f70
    }
    this->m_pCurrentTarget = newTarget;
    // Register new target if enabled and non-null
    if (((this->m_flags >> 8 & 1) != 0) && (newTarget != 0)) {
      registerTargetListener(newTarget, (int)this); // 0x6b0f70
    }
    // Check game mode (e.g., in-game vs editor)
    gameMode = getGameMode(); // 0x806440
    if (gameMode == 1) {
      if (this->m_pCurrentTarget != 0) {
        // Get wrapper/interface for the current target
        this->m_currentWrapper = getTargetWrapper(this->m_pCurrentTarget); // 0x6b0f50, stores at +0x2138
        debugFunction1(&g_debugData); // 0x408680 (DAT_0112a620)
        return;
      }
      // No target, set to default value
      this->m_currentWrapper = this->m_defaultValue; // +0x1ed4
      debugFunction2(&g_debugData); // 0x4086d0
    }
  }
}