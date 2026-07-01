// FUNC_NAME: TopDonChallenge::getCurrentScore
float TopDonChallenge::getCurrentScore(void)
{
  float result = 0.0f;
  
  if ((DAT_01129904 != 0) && (int* iVar1 = FUN_008c74d0(0x637b907), iVar1 != nullptr)) {
    // +0x120: current score (some integer value)
    int currentScore = *(int *)(iVar1 + 0x120);
    
    // +0x40: some base value, +0x44: some modifier, sum them for denominator
    int denominator = *(int *)(DAT_0112a558 + 0x44) + *(int *)(DAT_0112a558 + 0x40);
    
    // Normalize denominator to float (handling potential negative by adding DAT_00e44578, likely 2^32)
    float normalizedDenom = (float)denominator;
    if (denominator < 0) {
      normalizedDenom += (float)DAT_00e44578;
    }
    
    // Normalize current score similarly
    float normalizedScore = (float)currentScore;
    if (currentScore < 0) {
      normalizedScore += (float)DAT_00e44578;
    }
    
    // DAT_00d5e288: target threshold or maximum score value
    float maxScore = (float)DAT_00d5e288;
    
    // Compute ratio of current score to denominator, scaled by maxScore
    float calculated = normalizedScore * (maxScore / normalizedDenom);
    
    // Clamp to maxScore
    if (calculated <= maxScore) {
      return calculated;
    }
    result = maxScore;
  }
  return result;
}