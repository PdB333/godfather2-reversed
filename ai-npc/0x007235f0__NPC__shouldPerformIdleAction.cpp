// FUNC_NAME: NPC::shouldPerformIdleAction
bool __thiscall NPC::shouldPerformIdleAction(char param_forceCheck) {
  float fRandScale;
  int iTargetHandle;
  float fTargetInterest;

  // m_fIdleTimer (offset 0x130) accumulates time since last random action
  if (g_fIdleThreshold < *(float *)(this + 0x130)) {
    // If forceCheck is set, skip the random chance check
    if (param_forceCheck != '\0') {
      return true;
    }
    // Access a global manager pointer to get the current target (likely the player)
    // DAT_012233a0 is a global pointer to the manager; offset 0x4 is a pointer to the current target
    iTargetHandle = **(int **)(*(int *)0x12233a0 + 4);
    // 0x1f30 is a sentinel value meaning "no valid target"
    if (iTargetHandle != 0 && iTargetHandle != 0x1f30) {
      fTargetInterest = *(float *)(iTargetHandle + 0x1f8);  // m_fInterest (attractiveness)
      // Random roll: chance to perform action proportional to interest and idle timer
      if ((float)_rand() * g_fIdleRandomScale < fTargetInterest * *(float *)(this + 0x130)) {
        return true;
      }
    }
  }
  return false;
}