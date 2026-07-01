// FUNC_NAME: AudioSystem::calculateSoundLevelAndPan
void AudioSystem::calculateSoundLevelAndPan(float *outLevel, float *outPan)
{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_20;
  float local_1c;
  float local_18;
  
  cVar1 = FUN_00472510(&local_20); // Get sound origin vector (x,y,z)
  fVar4 = _DAT_00d5780c; // Master volume or distance threshold
  if (cVar1 == '\0') {
    return;
  }
  fVar3 = SQRT(local_1c * local_1c + local_18 * local_18 + local_20 * local_20) * DAT_00d5ddec; // Distance * scale factor
  *outLevel = fVar3;
  if (fVar3 <= fVar4) {
    if (*(float *)(DAT_01223464 + 0x1694) < fVar3) goto LAB_007d0dcb;
    fVar4 = *(float *)(DAT_01223464 + 0x1694) + DAT_00d5ef84; // Min volume + offset
  }
  *outLevel = fVar4;
LAB_007d0dcb:
  fVar2 = (float10)FUN_00799230(); // Get random pan value
  *outPan = (float)fVar2;
  return;
}