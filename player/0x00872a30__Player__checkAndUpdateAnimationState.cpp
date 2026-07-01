// FUNC_NAME: Player::checkAndUpdateAnimationState
void __fastcall Player::checkAndUpdateAnimationState(Player *this)
{
  // this +0x64 = m_animationState (some enum)
  char conditionFlag;
  int *animationController;

  if ( (this->m_animationState != 0) && (this->m_animationState != 0x48) ) {
    animationController = GetAnimationController();
    if (animationController != (int *)0x0) {
      // Call virtual function at vtable+0x2c (index 11)
      // Parameters: (loop=1, restart=1, blendTime=0, speed=1.0f, weight=1.0f)
      (*(code *)animationController->vtable[0x2c / 4])(animationController, 1, 1, 0, 1.0f, 1.0f);
    }
    conditionFlag = IsUIActive(); // Returns bool
    if (conditionFlag == 0) {
      SetGamePauseState(0); // unpause
      return;
    }
    SetGamePauseState(1); // pause
  }
  return;
}