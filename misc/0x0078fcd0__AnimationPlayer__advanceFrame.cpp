// FUNC_NAME: AnimationPlayer::advanceFrame
void __fastcall AnimationPlayer::advanceFrame(int *this)
{
  bool bIsPlaying;
  uint nextFrameIndex;
  int frameDataIndex;
  
  // Copy current frame index to previous frame index
  this[0x27] = this[0x28]; // +0x9C = previousFrameIndex, +0xA0 = currentFrameIndex
  
  // Advance to next frame index
  nextFrameIndex = this[0x28] + 1; // +0xA0 = currentFrameIndex
  if ((uint)this[0x25] <= nextFrameIndex) { // +0x94 = frameCount
    nextFrameIndex = 0xffffffff; // Wrap to -1 (end of animation)
  }
  this[0x28] = nextFrameIndex; // +0xA0 = currentFrameIndex
  
  bIsPlaying = true;
  
  // Check if there's a frame data pointer at current frame
  frameDataIndex = this[0x27] * 2 + 0x16; // +0x58 base for frame data array
  if (this[frameDataIndex] != 0) {
    // Check if the frame data has a valid animation event
    int eventResult = FUN_006b0ee0(this[frameDataIndex]); // CheckAnimationEvent
    if (eventResult != 0) {
      int soundResult = FUN_006b4860(); // CheckSoundEvent
      if (soundResult != 0) {
        bIsPlaying = false; // Animation has ended
      }
    }
  }
  
  // Set playing state
  *(bool *)(this + 0x2c) = !bIsPlaying; // +0xB0 = isFinished
  
  if (bIsPlaying) {
    // Call frame callback if animation is still playing
    int callbackResult = FUN_00791300(); // GetFrameCallback
    if (callbackResult != 0) {
      // Call the virtual frame callback function
      (**(code **)(*this + 0x20))(this[0x27], this + 0x29); // vtable+0x20 = onFrameCallback
    }
  }
}