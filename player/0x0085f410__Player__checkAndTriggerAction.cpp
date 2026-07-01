// FUNC_NAME: Player::checkAndTriggerAction
void __fastcall Player::checkAndTriggerAction(int *this)
{
  float10 fVar1;
  float dotResult;
  float forwardX;
  float forwardY;
  float forwardZ;
  float toTargetX;
  float toTargetY;
  float toTargetZ;
  float local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;

  // +0xF60: actionCooldownTimer (float)
  if ((float)this[0x3d8] <= 0.0f) {
    // +0xA30: getFacingDirection() - returns normalized forward vector
    fVar1 = (float10)FUN_004702b0(this + 0x28c);
    if (fVar1 <= (float10)DAT_00d5efa8) {
      // Get camera forward direction
      FUN_008750c0(&toTargetX);
      // Get target position relative to player
      FUN_00601970(this[0x452], &forwardX);
      local_20 = forwardX;
      local_1c = forwardY;
      local_18 = forwardZ;
      local_14 = 0;
      // Normalize the direction to target
      FUN_0056afa0(&local_20, &local_20);
      // Dot product check: is target in front of player?
      if (DAT_00d757e0 <= local_1c * toTargetY + local_20 * toTargetX + local_18 * toTargetZ) {
        return;
      }
    }
    // Call virtual function at +0x298 (likely performAction)
    (**(code **)(*this + 0x298))();
    // Play action animation (0 = action index)
    FUN_0087d560(0);
  }
  return;
}