// FUNC_NAME: AnimationStateManager::decrementRefCountAndCleanup
void __fastcall AnimationStateManager::decrementRefCountAndCleanup(int *this)
{
  int animStatePtr;
  short *refCountPtr;
  
  // Check if the state is active (1 == active) and has an allocated animation state
  if (((*this == 1) && (animStatePtr = this[1], animStatePtr != 0)) &&
     // Decrement reference count at offset +0x14 (probably refCount field)
     (*(short *)(animStatePtr + 0x14) = *(short *)(animStatePtr + 0x14) + -1, 
      *(short *)(animStatePtr + 0x14) < 1) &&
     // Check secondary field at +0x16 against global counter
     ((*(short *)(animStatePtr + 0x16) == g_globalAnimationCounter) &&
      (g_globalAnimationCounter = g_globalAnimationCounter + -1, -1 < g_globalAnimationCounter)))) {
    // Iterate through animation state array (0x20 bytes per entry starting at +4 offset from base)
    refCountPtr = (short *)((int)&g_animationStateArray + g_globalAnimationCounter * 0x20 + 4);
    do {
      if (0 < *refCountPtr) {
        return; // Still references exist, don't clean up
      }
      g_globalAnimationCounter = g_globalAnimationCounter + -1;
      refCountPtr = refCountPtr + -0x10; // Move to previous entry (0x10 shorts = 0x20 bytes)
    } while (-1 < g_globalAnimationCounter);
  }
  return;
}