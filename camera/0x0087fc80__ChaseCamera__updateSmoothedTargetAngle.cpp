// FUNC_NAME: ChaseCamera::updateSmoothedTargetAngle
void __thiscall ChaseCamera::updateSmoothedTargetAngle(ChaseCamera* this, void* target)
{
  float targetValue;       // fVar1
  float smoothedValue;     // fVar2
  float upperBound;        // fVar3
  float lowerBound;        // fVar3

  if (target != (void*)0x0) {
    // Get the desired angle/value from the target object (virtual function at vtable+0x1a8)
    targetValue = (*(float (__thiscall**)(void*))(*(int*)target + 0x1a8))(target);
    
    // Smooth the value: interpolate between current and target using some function (likely with delta time)
    smoothedValue = SmoothValueWithBounds( targetValue - *(float*)(this + 0x1c8),   // change from last frame
                                            *(float*)(this + 0x1c4),                // current smoothed value
                                            DAT_00d5c454 );                         // smoothing rate / delta
    *(float*)(this + 0x1c4) = smoothedValue;   // +0x1c4 = m_currentSmoothedValue

    // Clamp the result within valid range [lowerBound, upperBound]
    upperBound = _DAT_00d5780c;                 // upper bound constant
    if ( ((float10)1.0 < (float10)smoothedValue) || 
         (upperBound = DAT_00d5ccf8, (float)smoothedValue < DAT_00d5ccf8) )
    {
      *(float*)(this + 0x1c4) = upperBound;     // apply the clamped bound
    }
    
    // Store the raw target value for next frame's delta calculation
    *(float*)(this + 0x1c8) = targetValue;      // +0x1c8 = m_lastRawTargetValue
  }
}