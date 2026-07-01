// FUNC_NAME: AnimationPlayer::constructor
undefined4 * __fastcall AnimationPlayer::constructor(undefined4 *this)
{
  this[1] = 1;
  this[2] = 0;
  this[3] = &PTR_LAB_00d7d418;
  DAT_011299a0 = this;
  *this = &PTR_FUN_00d7d420;
  this[3] = &PTR_LAB_00d7d41c;
  if (DAT_012069d4 != 0) {
    // Copy 0x8000 bytes from global animation data buffer
    FUN_00408900(this,&DAT_012069d4,0x8000);
  }
  this[4] = 0;          // +0x10: currentFrame
  this[0xe] = 0;        // +0x38: startTime
  this[5] = 0;          // +0x14: blendWeight
  this[6] = 0;          // +0x18: playbackSpeed
  *(undefined1 *)(this + 0xd) = 0;  // +0x34: loopFlag
  this[0xf] = 0;        // +0x3c: endTime
  this[0x10] = 0;       // +0x40: duration
  *(undefined1 *)(this + 0x17) = 0; // +0x5c: isPaused
  this[0x18] = 0;       // +0x60: pauseFrame
  this[0x19] = 0;       // +0x64: pauseTime
  this[0x1a] = 0;       // +0x68: fadeOutDuration
  *(undefined1 *)(this + 0x21) = 0; // +0x84: isFinished
  this[0x22] = 0;       // +0x88: someFlag
  this[0x23] = 0;       // +0x8c: someValue
  this[0x24] = 0;       // +0x90: someValue2
  *(undefined1 *)(this + 0x2b) = 0; // +0xac: someBool
  return this;
}