// FUNC_NAME: Animated::blendAnimationParams
undefined4 __fastcall Animated::blendAnimationParams(void *this, float *blendParams)
{
  int animationState;
  char *blendMode;
  char *animationName;
  undefined localBuf[39];
  undefined4 result;

  animationState = getAnimationState(this);
  if (animationState != 0) {
    if (blendParams[7] != 0.0f) {
      blendMode = "REPLACE";
    } else {
      blendMode = "COMBINE";
    }
    doSomething(); // FUN_004d9080
    animationName = *(char **)(animationState + 0x2a0); // offset to current animation name
    if (animationName == (char *)0x0) {
      animationName = &DAT_0120546e; // default animation name
    }
    blendAnimationFrames(animationName,
                        (double)blendParams[0],
                        (double)blendParams[1],
                        (double)blendParams[3],
                        (double)blendParams[4],
                        (double)blendParams[5],
                        (double)blendParams[6],
                        blendMode,
                        localBuf);
    result = getBlendResult();
    return result;
  }
  return 0;
}