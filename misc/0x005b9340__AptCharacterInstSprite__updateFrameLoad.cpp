// FUNC_NAME: AptCharacterInstSprite::updateFrameLoad
void __fastcall AptCharacterInstSprite::updateFrameLoad(void *param_1)
{
  int *debugDataPtr;
  void (*breakHandler)(void);
  char assertionEnabled;
  uint debugFlags;
  int frameData;
  int fsOffset;
  char *assertFile;
  char *assertFunc;
  int assertLine;
  int assertLevel;
  char *assertCondition;

  // Assertion check for isSpriteInstBase()
  assertionEnabled = Assertion::isEnabled();
  if (assertionEnabled != '\0') goto LAB_005b93df;

  assertFunc = "isSpriteInstBase()";
  assertFile = "..\\source\\Apt\\AptCharacterInstSprite.cpp";
  assertLine = 0x147;
  assertLevel = 2;
  assertCondition = (char *)&DAT_01129146;
  if (DAT_01129146 == '\0') goto LAB_005b93df;

  debugDataPtr = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
  debugFlags = 1;
  if (debugDataPtr == (int *)0x0) {
LAB_005b93bd:
    if ((debugFlags & 2) != 0) {
      *assertCondition = 0;
    }
  }
  else {
    debugFlags = (**(code **)(*debugDataPtr + 8))(&assertFile, "isSpriteInstBase()");
    if (assertCondition != (char *)0x0) goto LAB_005b93bd;
  }

  if (((debugDataPtr != (int *)0x0) || (assertLevel != 4)) &&
     (((debugFlags & 1) != 0 || ((assertLevel == 0 || (assertLevel == 1)))))) {
    breakHandler = (code (*)(void))swi(3);
    (*breakHandler)();
    return;
  }

LAB_005b93df:
  // State machine update for sprite loading
  frameData = AnimationState::getInstance();
  if ((*(byte *)(frameData + 0x17) & 1) != 0) {
    *(int *)(frameData + 0x10) = *(int *)(frameData + 0x10) + 1;
    if ((*(int *)(frameData + 0x10) == 1) && (*(int *)(*(int *)(frameData + 8) + 8) == 1)) {
      *(undefined4 *)(frameData + 0x10) = 0;
      AptCharacterInstSprite::submitFrame();
      return;
    }
    if (*(int *)(frameData + 0x10) == *(int *)(*(int *)(frameData + 8) + 8)) {
      AptCharacterInstSprite::finishPreloading(0);
      AptCharacterInstSprite::submitFrame();
      return;
    }
  }

  if ((*(byte *)(frameData + 0x17) & 1) != 0) {
    AptCharacterInstSprite::processFrameData(*(int *)(frameData + 8) + 8, frameData + 0x1c, param_1, *(undefined4 *)(frameData + 0x10));
  }

  if ((*(byte *)(frameData + 0x17) & 1) != 0) {
    AptCharacterInstSprite::processFrameFinished(*(int *)(frameData + 8) + 8, param_1);
  }

  AptCharacterInstSprite::submitFrame();
  return;
}