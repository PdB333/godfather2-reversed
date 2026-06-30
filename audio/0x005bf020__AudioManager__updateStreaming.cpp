// FUNC_NAME: AudioManager::updateStreaming
void AudioManager::updateStreaming(void)

{
  char cVar1;
  uint uVar2;
  float fVar3;
  
  // Calculate time delta, wrapping around if negative (handles overflow)
  fVar3 = (float)(DAT_01205210 - _DAT_0120564c);
  if (DAT_01205210 - _DAT_0120564c < 0) {
    fVar3 = fVar3 + DAT_00e44578; // +0x0: float constant for wrap-around
  }
  fVar3 = fVar3 * DAT_00e2e210; // +0x0: time scale factor
  _DAT_0120564c = DAT_01205210; // Store current time for next frame
  DAT_01205654 = 0; // Reset some flag
  
  // Check if streaming is active and there's a valid stream object
  if ((((DAT_01205648 < 1) && (-1 < DAT_00f17914)) &&
      ((int *)(&DAT_01205608)[DAT_00f17914] != (int *)0x0)) &&
     (cVar1 = (**(code **)(*(int *)(&DAT_01205608)[DAT_00f17914] + 0x10))(fVar3), cVar1 == '\\0')) {
    // Stream update returned 0 (not finished)
    if (DAT_00f17964 < 0x10) {
      // Low priority: try to start a new stream
      cVar1 = FUN_004667f0(); // Check if can start new stream
      if (cVar1 != '\\0') {
        FUN_005bed10(fVar3); // Start streaming
        return;
      }
    }
    else if (DAT_00f17964 != 0x12) {
      // Higher priority: try multiple times to start a stream
      uVar2 = 0;
      do {
        cVar1 = FUN_004667f0(); // Check if can start new stream
        if ((cVar1 != '\\0') && (cVar1 = FUN_005bed10(fVar3), cVar1 != '\\0')) {
          return;
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < 0x10); // Try up to 16 times
    }
  }
  return;
}