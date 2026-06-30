// FUNC_NAME: Animation::setSpeed
void __thiscall Animation::setSpeed(float ratio)
{
    float clamped;
    // Normalize by a global base speed factor
    ratio = ratio / s_baseSpeed; // _DAT_0112a7a8
    // Store normalized value first (may be overwritten if clamping applies)
    m_speed = ratio; // +0x60
    // Clamp: if value <= 0.0 OR >= s_maxSpeed, set to s_maxSpeed
    // Note: This clamping forces 0.0 to become s_maxSpeed – likely intentional design
    clamped = 0.0f;
    if (ratio <= 0.0f || (clamped = s_maxSpeed, s_maxSpeed <= ratio)) {
        ratio = clamped;
    }
    m_speed = ratio; // +0x60 final value
}