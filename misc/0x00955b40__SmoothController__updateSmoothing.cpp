// FUNC_NAME: SmoothController::updateSmoothing
void __thiscall SmoothController::updateSmoothing(float dt)
{
    // Offset map:
    // +0x60 : m_startValue (initial value for lerp)
    // +0x70 : m_targetValue (target value for lerp)
    // +0x90 : m_outputValue (result of lerp/smoothing)
    // +0xa4 : m_previousTarget (previous target for smoothing)
    // +0xa8 : m_scaleDenominator (denominator for ratio calculation)
    // +0xb0 : m_speed (smoothing speed factor)
    // +0xb4 : m_currentSmoothValue (current smoothed value)
    // +0xb8 : m_smoothThreshold (threshold to switch to linear interpolation)
    // +0xcc : m_scaleNumerator (numerator for ratio)

    float previousTarget = *(float*)(this + 0xa4);
    float currentSmooth = *(float*)(this + 0xb4);
    float speed = *(float*)(this + 0xb0);
    
    // Compute damping factor: currentSmooth divided by (lerp(g_timeStep, speed, dt))
    // g_timeStep is a global constant (likely frame time or natural decay)
    float denom = (speed - g_timeStep) * dt + g_timeStep;
    float dampedValue = currentSmooth / denom;
    
    // Take the maximum of previous target and damped value
    float newSmooth = previousTarget;
    if (previousTarget < dampedValue) {
        newSmooth = dampedValue;
    }
    
    float threshold = *(float*)(this + 0xb8);
    *(float*)(this + 0xb4) = newSmooth; // Update current smooth value
    
    // Compute scaled output using ratio of two fields
    float scaleNum = *(float*)(this + 0xcc);
    float scaleDenom = *(float*)(this + 0xa8);
    *(float*)(this + 200) = (scaleNum / scaleDenom) * newSmooth;
    
    // If newSmooth <= threshold, perform linear interpolation between start and target
    if (newSmooth <= threshold) {
        float lerpFactor = (threshold - newSmooth) / (threshold - previousTarget);
        float startValue = *(float*)(this + 0x70);
        float targetValue = *(float*)(this + 0x60); // Note: 0x60 before 0x70, but used as end? Possibly swapped.
        *(float*)(this + 0x90) = startValue - (startValue - targetValue) * lerpFactor;
    }
}