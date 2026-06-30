// FUNC_NAME: PlayerActionableInfo::getScore
float __thiscall PlayerActionableInfo::getScore(void *this, uint targetId) {
  // Check global score time threshold against this object's score time
  if (g_minScoreThreshold < (float)((int *)this)[0x209]) {
    return 0.0f;
  }

  // If validation flag is set, check if target is valid for action
  if (((int *)this)[0x17d] != 0) {
    if (!isTargetValidForAction(targetId)) {
      goto returnZero;
    }
  }

  // Call virtual method at vtable+0x228 (e.g., isTargetReachable)
  if (!callVirtualMethod(this, 0x228, targetId)) {
    // Virtual method returned false (e.g., target not reachable)
    int actionState = ((int *)this)[0x801];
    if (actionState != 0 && actionState != 0x48) {
      // State is neither idle nor combat -> compute fallback score
      return computeFallbackScore();
    }
    // Return base score at offset 0x75f (float)
    return (float)((int *)this)[0x75f];
  }

returnZero:
  return 0.0f;
}