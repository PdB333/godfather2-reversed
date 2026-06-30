//FUNC_NAME: AnimationManager::updateAnimations
void __thiscall AnimationManager::updateAnimations(void)
{
  int iVar1;
  float fVar2;
  
  // Check if accumulated time is within fixed step
  if (g_accumulatedTime <= g_fixedTimeStep) {
    // Get pointer to animation array descriptor at this+0x4
    // Descriptor: first element is pointer to array, second is count
    iVar1 = *(int *)(*(int *)(this + 4) + 0); // array base
    fVar2 = g_timeScale / g_fixedTimeStep; // compute time ratio
    
    // Loop over array elements (each 0x70 bytes)
    if (iVar1 != (*(int *)(*(int *)(this + 4) + 4) * 0x70 + iVar1)) {
      do {
        // Check if animation is active: at offset 0x40 is a pointer, offset 8 is a flag
        if (*(int *)(*(int *)(iVar1 + 0x40) + 8) != 0) {
          Animation::update(fVar2); // update animation with time ratio
        }
        iVar1 = iVar1 + 0x70; // advance to next animation
      } while (iVar1 != (*(int *)(*(int *)(this + 4) + 4) * 0x70 + *(int *)(*(int *)(this + 4) + 0)));
    }
  }
  return;
}