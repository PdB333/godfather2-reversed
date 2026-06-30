// FUNC_NAME: StreamPlayer::update
void __thiscall StreamPlayer::update(StreamPlayer *this, float deltaTime)
{
  int *pThreadLocal;
  int threadIndex;
  int streamData;
  int *pHandle; // &this->mStreamHandle
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint *puVar7;
  float modifierValue;
  float volumeTarget;
  float volumeL;
  float volumeR;
  float local_2c;
  float local_28;
  char local_20[28]; // unused padding?

  // Get thread-local storage (FS segment)
  pThreadLocal = *(int **)(__readfsdword(0x2c) + 0x2c);
  threadIndex = pThreadLocal[2] + 4; // +8? Actually iVar3 points to something, iVar4 = *(iVar3+8)
  iVar4 = pThreadLocal[2] + 8; // Wait, let's recalc: iVar3 = **(int **)(FS+0x2c); iVar4 = *(iVar3+8);
  // Actually from decomp: iVar3 = **(int **)(unaff_FS_OFFSET + 0x2c); iVar4 = *(int *)(iVar3 + 8);
  // So iVar3 is a pointer from TLS, then iVar4 is a value at that pointer+8.
  // Then iVar6 = param_1[4] (offset 0x10) + iVar4.
  int *basePtr = pThreadLocal[2]; // maybe thread state?
  int offsetInThread = basePtr[2]; // from +8? Wait, need to be careful.
  // Let's keep as decompiled: iVar4 = *(iVar3+8), then iVar6 = param_1[4] + iVar4.
  // So param_1[4] is an offset into some thread-local array? 
  // The bit test: if ((*(byte *)(param_1[4] + iVar4) & 1) != 0) return;
  // So there's a flag at (this->mThreadOffset + threadIndex) or similar.
  int flagAddress = this->field_0x10 + iVar4; // param_1[4] at offset 0x10
  if ((*(byte *)flagAddress & 1) != 0) {
    return;
  }

  pHandle = &this->mStreamHandle; // param_1 + 0x30

  // State machine for audio playback
  if (this->mStreamHandle == 0 || this->mFinished != 0) {
    if (this->mFinished == 0) {
      // Not finished, so handle starting/stopping based on playback mode
      if (this->mPlaybackMode < 0) {
        // Playback mode negative? call stop/reset
        FUN_004eaec0(this->field_0x24 + 8, local_20); // reset stream state
        FUN_004b1a10(flagAddress + 0x80, *(this->mContext + 0x84)); // stop?
      } else {
        // Start streaming
        FUN_004b1b00(pHandle, this->field_0x24 + 8, flagAddress + 0x80, *(this->mContext + 0x84));
      }
    } else {
      // mFinished is set
      if (this->field_0x34 == 0) {
        // Call a virtual method (likely OnFinish)
        (this->vtable->onFinish)(this);
      } else {
        // Reset handle and finished flag
        this->mStreamHandle = 0;
        this->mFinished = 0;
      }
    }
  } else {
    // Stream is active and not finished, update it
    FUN_004b1c40(flagAddress + 0x80, *(this->mContext + 0x84));
  }

  // Volume calculations
  local_28 = *(float *)(this->field_0x24 + 0x18); // base volume?
  local_2c = DAT_00e2b1a4; // global default volume?

  // Apply DSP or effect volume modifier
  if ((*(int *)(this->mContext + 0xb0) - 1 < 4) &&
      (piVar5 = *(int **)(this->mContext + 0xb4), piVar5 != (int *)0x0)) {
    // Call virtual function at offset 0x110 on the effect object
    float effectVolume = (float)(*(code **)(*piVar5 + 0x110))();
    local_2c = effectVolume;
  }

  // Apply volume modifier from a referenced asset
  if (this->mVolumeModifier != 0) {
    int modRef = this->mVolumeModifier;
    if (modRef != 0) {
      *(int *)(modRef + 4) = *(int *)(modRef + 4) + 1; // reference counting increment
    }
    int *modPtr = FUN_00500630(modRef); // get modifier data
    if (modPtr != 0) {
      local_28 = *(float *)(modPtr + 0xc) * local_28;
      local_2c = *(float *)(modPtr + 8) * local_2c;
    }
  }

  // Clamp local_2c between min and max global values
  float minVol = DAT_00e44940;
  if ((local_2c <= minVol) || (minVol = DAT_00e2b04c, DAT_00e2b04c <= local_2c)) {
    local_2c = minVol;
  }

  // Update volume for left channel (if changed)
  if (local_2c != (float)this->mCurrentVolumeL) {
    if (this->mStreamHandle != 0) {
      FUN_005e6750(this->mStreamHandle, local_2c);
    }
    this->mCurrentVolumeL = (int)local_2c;
  }

  // Compute right volume (or general volume)
  if (local_28 > 0.0f) {
    volumeR = DAT_00e2b1a4; // default right volume
    if (local_28 < DAT_00e2b1a4) goto LABEL_SET_R;
  } else {
    volumeR = 0.0f;
  }
  volumeR = local_28;
LABEL_SET_R:
  local_28 = volumeR;

  // Update volume for right channel (if changed)
  if (volumeR != (float)this->mCurrentVolumeR) {
    if (this->mStreamHandle != 0) {
      FUN_005e6700(this->mStreamHandle, local_28);
      volumeR = local_28; // update local after call? Actually in decomp, they reassign fVar9 = local_28 after call
    }
    this->mCurrentVolumeR = (int)volumeR;
  }

  // Accumulate time and check for stop threshold
  if (*(float *)(this->field_0x24 + 4) > 0.0f) {
    this->mTimeAccumulator += deltaTime;
    if (*(float *)(this->field_0x24 + 4) <= this->mTimeAccumulator &&
        this->mTimeAccumulator != *(float *)(this->field_0x24 + 4)) {
      // Set stop flag
      uint *stopFlag = (uint *)(flagAddress);
      *stopFlag |= 1;
    }
  }
}