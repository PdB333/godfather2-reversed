// FUNC_NAME: PlayerSM::updateFadeToBlack
void __fastcall PlayerSM::updateFadeToBlack(int *this)
{
  float fVar1;
  float fVar2;
  char cVar3;
  float10 fVar4;
  float10 fVar5;
  float fStack_c;

  // Check if fade target exists and is not active, and if fade flag is not set
  if ((((this[0x17d] == 0) || // +0x5F4: fadeTarget
       (cVar3 = (**(code **)(*(int *)this[0x17d] + 0x38))(), cVar3 == '\0')) && // isFadeActive()
      (((uint)this[0x238] >> 0x17 & 1) == 0)) && // +0x8E0: flags, bit 23 = fadeDisabled
     ((cVar3 = FUN_00481620(), cVar3 != '\0' && // isGamePaused()
      (cVar3 = FUN_00481660(), fVar2 = DAT_012067e8, cVar3 == '\0')))) { // isCutsceneActive()
    fVar4 = (float10)(**(code **)(*this + 0xc0))(); // getCurrentFadeLevel()
    fVar5 = (float10)(**(code **)(*this + 0xc4))(); // getTargetFadeLevel()
    fVar1 = (float)fVar5;
    if ((float10)(float)fVar4 < fVar5) {
      fStack_c = (float)this[0x75b] * fVar2 + (float)fVar4; // +0x1D6C: fadeSpeed * deltaTime + currentFade
      if (fVar1 <= fStack_c) {
        fStack_c = fVar1;
      }
      if (((uint)this[0x208] >> 6 & 1) != 0) { // +0x820: flags, bit 6 = instantFade
        fStack_c = fVar1;
      }
      (**(code **)(*(int *)this[0x17d] + 0x3c))(fStack_c); // setFadeLevel()
    }
  }
  return;
}