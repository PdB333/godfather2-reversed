// FUNC_NAME: AnimatedObject::setAnimationState
void AnimatedObject::setAnimationState(int state)
{
  // +0xe8: animation state ID
  this->state = state;

  if (state != 2 && state != 3) {
    // For non-2/3 states: copy custom flags to owner's state flags and play
    // +0x18: pointer to owner object (e.g., SimObject)
    // +0x2c: owner's state flags bitfield
    // +0xd4: this object's custom flags
    this->owner->stateFlags = this->customFlags; // [this+0xd4]
    this->updateAnimator(this->owner, 1); // 1 = play
    return;
  }

  // For state 2 or 3: lookup base animation ID and set up state
  uint baseAnimId = (state == 2) ? 0xd : 0x14; // +0xd for state 2, +0x14 for state 3

  uint currentFlags = this->owner->stateFlags;
  uint extracted = 0;

  // Extract 12-bit value from flags based on top two bits
  uint topBits = currentFlags & 0xC0000000;
  if (topBits == 0) {
    extracted = currentFlags >> 0x10;
  } else if (topBits == 0x40000000) {
    // Indirect table lookup: ushort at index*4 + 2
    extracted = *(ushort*)(currentFlags * 4 + 2);
  } else if (topBits == 0xC0000000) {
    // Indirect table lookup: ushort at index*4 + 0x4e
    extracted = *(ushort*)(currentFlags * 4 + 0x4e);
  } // else extracted = 0
  extracted &= 0xFFF; // 12-bit value

  // +0xb0: timer (reset to 0)
  this->timer = 0;

  // Construct new flags: extracted in high 16 bits, baseAnimId in low 16 bits, plus flags 0x3e0
  this->owner->stateFlags = (extracted << 0x10) | baseAnimId | 0x3e0;

  this->updateAnimator(this->owner, 0); // 0 = stop/update
}