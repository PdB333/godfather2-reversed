// FUNC_NAME: AnimationController::setAnimationSegment
void __thiscall AnimationController::setAnimationSegment(int this, int animSet, int segmentIndex, float startTime, float endTime, float blendDuration)
{
  float globalStartTime = DAT_01205228; // global animation start time offset
  if (animSet == 0) {
    *(int *)(this + 0x10) = (int)&DAT_00e53b50; // null animation set, use default
  }
  else {
    *(int *)(this + 0x10) = segmentIndex * 0x22c + *(int *)(animSet + 0x38); // +0x38: animation set segment array offset
  }
  int oldSegmentIndex = *(int *)(this + 0x14); // +0x14: current segment index
  *(int *)(this + 0x14) = segmentIndex;
  if (segmentIndex != oldSegmentIndex) {
    *(float *)(this + 0x18) = globalStartTime; // +0x18: segment start time
    *(float *)(this + 0x1c) = globalStartTime + startTime; // +0x1c: segment local start time
  }
  float segmentEndTime = globalStartTime + startTime + endTime;
  *(float *)(this + 0x20) = segmentEndTime; // +0x20: segment end time
  *(float *)(this + 0x24) = segmentEndTime + blendDuration; // +0x24: blend out time
  return;
}