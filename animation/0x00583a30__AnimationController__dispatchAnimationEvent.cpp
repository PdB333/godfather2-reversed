// FUNC_NAME: AnimationController::dispatchAnimationEvent
undefined4 __thiscall AnimationController::dispatchAnimationEvent(byte *this, undefined4 param_2, undefined4 param_3, float param_4, float param_5, undefined4 param_6, float param_7, float param_8)
{
  undefined4 result;
  
  // Check if animation event type is valid (0x23 = 35, max event types)
  if ((*this & 0x3f) < 0x23) {
    // Scale animation parameters by time scale factor
    param_7 = DAT_00e2b1a4 / param_7;  // DAT_00e2b1a4 is likely a base time scale constant
    
    // Call the appropriate event handler function from the vtable
    // The vtable is at DAT_0103afc0, indexed by event type (masked to 6 bits)
    result = (**(code **)(&DAT_0103afc0 + (*this & 0x3f) * 4))
                      (param_2, this, param_3, param_7 * param_4, param_7 * param_5, param_6,
                       param_7 * param_8);
    return result;
  }
  
  // Invalid event type, return 0
  return 0;
}