// FUNC_NAME: AnimationManager::setupTaskAnimationSystem
void AnimationManager::setupTaskAnimationSystem(void)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0x2b3c);  // Memory allocation? Check if memory for task animation data exists
  if (iVar1 != 0) {
    DAT_01129878 = FUN_00681840();  // Initialize task animation manager
    return;
  }
  DAT_01129878 = 0;  // No memory available, set to null
  return;
}