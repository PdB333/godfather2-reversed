// FUNC_NAME: AudioManager::calculateVolumeAttenuation
float AudioManager::calculateVolumeAttenuation(float distance, int *audioObj)
{
  int *objPtr;
  float attenuation;
  float distanceSq;
  
  objPtr = audioObj;
  FUN_008767c0(distance, &attenuation, &audioObj);
  distance = _DAT_00d5780c;
  float maxDist = (**(code **)(*objPtr + 0x1a8))(); // +0x1A8: getMaxAudibleDistance
  if ((float)DAT_00e446c0 < maxDist) {
    distance = (DAT_00e446c0 / maxDist) * (DAT_00e446c0 / maxDist);
  }
  return (float)distance * attenuation;
}