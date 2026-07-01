// FUNC_NAME: PlayerF2FSM::calculateInterceptionHeading
void PlayerF2FSM::calculateInterceptionHeading(float *playerFacing, Vector2 *targetRelPos, float *outResult)
{
  float fPlayerYaw;
  bool bValidIntercept;
  float fTargetSpeed;
  float fTargetRelX;
  float fTargetRelY;
  float fPlayerSpeed;
  float fDotProduct;
  float fDistance;
  float fLocal_1c;
  
  fTargetSpeed = DAT_00d71c5c;  // global speed threshold/tuning value
  fTargetRelY = *(float *)(targetRelPos + 1);  // target relative Y position
  fLocal_1c = (float)*targetRelPos;  // target relative X position
  fPlayerSpeed = playerFacing[1];  // player speed (likely from facing/velocity vector)
  fDistance = SQRT(fTargetRelY * fTargetRelY + fLocal_1c * fLocal_1c);  // distance to target
  fPlayerYaw = *playerFacing;  // player yaw/direction
  // Check if player is facing roughly towards target and target is far enough
  fDotProduct = fPlayerYaw * fLocal_1c + fPlayerSpeed * 0.0f + fTargetRelY * playerFacing[2];
  if ((0.0f < fDotProduct) && (DAT_00d5ef84 < fDistance)) {
    // Calculate time to intercept based on relative speeds
    fTargetRelY = 0.0f;
    if (0.0f < fPlayerSpeed) {
      // Ratio of player speed to target movement speed
      fTargetRelY = SQRT(playerFacing[2] * playerFacing[2] + fPlayerYaw * fPlayerYaw) / fPlayerSpeed;
    }
    // Calculate interception heading offset
    fPlayerSpeed = DAT_00e44564 - fTargetRelY * fDistance;  // constant - (time ratio * distance)
    bValidIntercept = fPlayerSpeed <= DAT_00d71c5c;  // check if in range
    *(float *)(outResult + 4) = fPlayerSpeed;
    if ((bValidIntercept) || (fTargetSpeed = DAT_00d648f4, DAT_00d648f4 <= fPlayerSpeed)) {
      fPlayerSpeed = fTargetSpeed;  // clamp to min/max values
    }
    *(float *)(outResult + 4) = fPlayerSpeed;
  }
  return;
}