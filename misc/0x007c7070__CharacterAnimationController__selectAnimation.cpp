// FUNC_NAME: CharacterAnimationController::selectAnimation
void __fastcall CharacterAnimationController::selectAnimation(int *this)
{
  int animId;
  int state;

  // Check if game is in a special mode (e.g., cutscene, vehicle) and if a specific flag is set
  if ((FUN_007ab1e0() != 0) && ((*(uint *)(this[0x16] + 0x8e0) >> 10 & 1) != 0)) {
    // Special mode: determine animation based on movement state
    state = FUN_00701050(); // getMovementState()
    if (state == 2) {
      // State 2: e.g., walking
      animId = (this[0x46] != 2) ? 0x26ea6033 : 0x6324d1e8;
      // 0x6324d1e8 likely ANIM_WALK, 0x26ea6033 something else
    } else {
      state = FUN_00701050(); // re-read? Possibly a different function
      if (state == 3) {
        // State 3: e.g., running
        animId = this[0x46]; // use current state directly
      } else {
        state = FUN_00701050();
        if (state == 4) {
          // State 4: e.g., sprinting
          animId = (this[0x46] != 2) ? 0x824601a1 : 0x7c9307a;
        } else {
          // Default fallback
          animId = (this[0x46] != 2) ? 0xa2939c9 : 0x95099fbd;
        }
      }
    }
  } else {
    // Normal mode: use simple state mapping
    animId = (this[0x46] != 2) ? 0xa2939c9 : 0x95099fbd;
  }

  // Call virtual function at vtable+0x2c (likely playAnimation or setAnimation)
  // Parameters: animId, 1, 1, 1, 1.0f, 1.0f
  (**(code **)(*this + 0x2c))(animId, 1, 1, 1, 0x3f800000, 0x3f800000);
}