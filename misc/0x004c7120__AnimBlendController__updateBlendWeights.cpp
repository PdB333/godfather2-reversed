// FUNC_NAME: AnimBlendController::updateBlendWeights
void AnimBlendController::updateBlendWeights(void)
{
  int copyCount;
  int destStartIndex;
  int *srcBuffer;
  int *destBuffer;
  int *blendTarget;
  int *blendTarget2;
  int *entry;
  uint idx;
  int entryOffset;
  
  // Check if current frame differs from previous frame and state is not paused (2)
  if ((this->previousFrame != this->currentFrame) && (this->state != 2)) {
    idx = 0;
    if (this->entryCount != 0) {
      entryOffset = 0;
      do {
        entry = (int *)(this->entryArray + entryOffset);
        int entityPtr = entry[1]; // Offset 0x04
        // Check if object has blend flag at +0xB2 and blend target is valid
        if (((*(byte *)(entry[0] + 0xb2) & 1) != 0) && (entry[(this->currentFrame & 1U) + 5] != 0)) {
          // Stop current animation on this entity
          FUN_00459b30(entityPtr, 1);
          // If entity's animation controller is not active, abort all
          if (*(char *)(*(int *)(entityPtr + 0x50) + 0x2f) == '\0') {
            return;
          }
          copyCount = entry[3]; // Number of elements to copy (offset 0x0C)
          destBuffer = (int *)FUN_0060bd50(); // Get destination buffer base
          destStartIndex = entry[4]; // Starting index in destination (offset 0x10)
          // Select blend source based on frame index (offset 0x2D in animation controller)
          uint blendSourceIdx = (uint)*(byte *)(*(int *)(entityPtr + 0x50) + 0x2d);
          blendTarget = *(int **)(entityPtr + 100 + (blendSourceIdx ^ 1) * 4);
          srcBuffer = (int *)FUN_0060bdb0(); // Get source buffer (probably previous frame's data)
          int *currentDest = destBuffer + destStartIndex * 1; // Actually destBuffer + destStartIndex * sizeof(int)? but code uses pointer arithmetic on int*
          // Copy 3 ints per iteration (probably position/rotation)
          for (; copyCount != 0; copyCount--) {
            *currentDest = *srcBuffer;
            currentDest[1] = srcBuffer[1];
            currentDest[2] = srcBuffer[2];
            currentDest += 3;
            srcBuffer += 5; // Skip 2 additional ints (maybe padding or unused)
          }
          // Update blend target flags
          if (*(char *)(blendTarget + 7) == '\0') {
            *(char *)((int)blendTarget + 0x1d) = 0;
          }
          else {
            // Call virtual method at offset 0x30 on blend target's object
            (*(void (__thiscall **)(int *))(*(int *)*blendTarget + 0x30))((int *)*blendTarget);
          }
          // Update second blend target (ping-pong)
          blendTarget2 = (int *)entry[(this->currentFrame & 1U) + 5];
          if (*(char *)(blendTarget2 + 7) == '\0') {
            *(char *)((int)blendTarget2 + 0x1d) = 0;
          }
          else {
            (*(void (__thiscall **)(int *))(*(int *)*blendTarget2 + 0x30))((int *)*blendTarget2);
          }
        }
        entryOffset += 0x1c; // Each entry is 28 bytes
        idx++;
      } while (idx < (uint)this->entryCount);
    }
    this->previousFrame = this->currentFrame;
  }
  return;
}