// FUNC_NAME: AudioManager::calculateVolumeFalloff
float __thiscall AudioManager::calculateVolumeFalloff(int this, int soundHandle)
{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float result;
  
  result = _DAT_00d5780c; // Default volume (likely 1.0f)
  if (soundHandle != 0) {
    iVar1 = FUN_00471610(); // Get listener position
    iVar2 = FUN_00471610(); // Get sound source position
    fVar5 = *(float *)(iVar2 + 0x38) - *(float *)(iVar1 + 0x38); // Z difference
    fVar3 = *(float *)(iVar2 + 0x30) - *(float *)(iVar1 + 0x30); // X difference
    fVar4 = *(float *)(iVar2 + 0x34) - *(float *)(iVar1 + 0x34); // Y difference
    iVar1 = *(int *)(this + 0x58); // Audio settings pointer
    fVar3 = SQRT(fVar5 * fVar5 + fVar3 * fVar3 + fVar4 * fVar4); // Distance
    if (fVar3 <= *(float *)(iVar1 + 0x1fe0)) { // Min distance
      return (float)*(float *)(iVar1 + 0x1fe8); // Max volume
    }
    if (fVar3 < *(float *)(iVar1 + 0x1fe4)) { // Max distance
      result = ((fVar3 - *(float *)(iVar1 + 0x1fe0)) /
               (*(float *)(iVar1 + 0x1fe4) - *(float *)(iVar1 + 0x1fe0))) *
               (_DAT_00d5780c - *(float *)(iVar1 + 0x1fe8)) + *(float *)(iVar1 + 0x1fe8);
    }
  }
  return (float)result;
}