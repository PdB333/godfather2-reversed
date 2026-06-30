// FUNC_NAME: AudioManager::updateListenerProximity
void __thiscall AudioManager::updateListenerProximity(int this, int soundSource, undefined4 param_3)
{
  float *pfVar1;
  int iVar2;
  int unaff_FS_OFFSET;
  float fVar3;
  float local_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float local_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  iVar2 = *(int *)(this + 4); // +0x4: audioManager internal data
  local_30 = *(float *)(soundSource + 0x100); // +0x100: sound source position X
  fStack_2c = *(float *)(soundSource + 0x104); // +0x104: sound source position Y
  fStack_28 = *(float *)(soundSource + 0x108); // +0x108: sound source position Z
  fStack_24 = DAT_00e2b1a4; // global listener position W (or time)
  pfVar1 = (float *)(*(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + 0x80 +
                    *(int *)(iVar2 + 0x10)); // +0x10: listener offset in audio data
  local_20 = local_30 - *pfVar1; // delta X
  fStack_1c = fStack_2c - pfVar1[1]; // delta Y
  fStack_18 = fStack_28 - pfVar1[2]; // delta Z
  fStack_14 = DAT_00e2b1a4 - pfVar1[3]; // delta W
  fVar3 = fStack_1c * fStack_1c + fStack_18 * fStack_18 + local_20 * local_20; // squared distance
  if ((*(float *)(iVar2 + 0x30) <= fVar3) && (fVar3 < *(float *)(iVar2 + 0x34))) { // +0x30: min distance, +0x34: max distance
    fVar3 = SQRT(fVar3); // actual distance
    FUN_004f8980(); // updateAudioState
    if (DAT_00e2e210 < fVar3) { // global threshold
      FUN_004f8aa0(soundSource, &local_30, fVar3, param_3, 0xffffffff); // playSoundAtPosition
    }
  }
  return;
}