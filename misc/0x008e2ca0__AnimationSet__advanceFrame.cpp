// FUNC_NAME: AnimationSet::advanceFrame
undefined1 __fastcall AnimationSet::advanceFrame(int this)
{
  int currentFrame;
  undefined1 result;
  
  currentFrame = *(int *)(this + 0x1dc);  // +0x1dc animationFrameIndex
  result = 1;
  if (currentFrame == -1) {
    *(undefined4 *)(this + 0x1dc) = 0;   // Reset to frame 0
    return result;                        // Return 1 (success, advanced)
  }
  
  *(int *)(this + 0x1dc) = currentFrame + 1;  // Advance frame
  
  if ((2 < currentFrame + 1) || 
      (*(int *)((currentFrame + 0x10) * 0x20 + this) == 0)) {
    // Frame past valid range OR next animation block pointer is null
    *(undefined4 *)(this + 0x1dc) = 0xffffffff;  // Set to -1 (done)
    result = 0;  // Return 0 (animation complete)
  }
  
  return result;  // Return 1 if still advancing, 0 if finished
}