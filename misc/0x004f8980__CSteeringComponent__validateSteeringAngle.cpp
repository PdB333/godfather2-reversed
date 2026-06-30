// FUNC_NAME: CSteeringComponent::validateSteeringAngle
void __thiscall CSteeringComponent::validateSteeringAngle(CSteeringComponent* this, float desiredAngle)
{
    // +0x24: pointer to a sub-structure containing angle limits (CSteeringLimits)
    CSteeringLimits* pLimits = *(CSteeringLimits**)((int)this + 0x24);
    
    // +0x18: reference angle (e.g., current steering angle)
    float referenceAngle = pLimits->referenceAngle; // offset +0x18
    // +0x1c: dead zone or delta (e.g., max allowed deviation)
    float delta = pLimits->delta; // offset +0x1c

    // Global absolute value mask (likely 0x7FFFFFFF to clear sign bit)
    const float absMask = *(float*)&DAT_00e44680; // constant: 0x7FFFFFFF interpreted as float
    // Global maximum turning authority threshold
    const float maxAuthority = *(float*)&DAT_00e2e780;

    if (desiredAngle < referenceAngle)
    {
        // If desired angle is less than reference, check if reference's absolute value exceeds maximum authority
        if (maxAuthority < *((float*)&absMask & (int&)referenceAngle)) // equivalent to fabs(referenceAngle)
        {
            return; // no action – steering likely disabled
        }
        return; // otherwise also return (no action)
    }
    else
    {
        // If desired angle >= reference, check if the absolute difference exceeds maximum authority
        float error = referenceAngle - delta; // note: subtraction order might be intentional
        if (maxAuthority < *((float*)&absMask & (int&)error)) // fabs(error)
        {
            return; // no action – steering clamped
        }
        return; // otherwise also return
    }
}