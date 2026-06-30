// FUNC_NAME: Math::eulerAnglesToQuaternion
void eulerAnglesToQuaternion(float pitchDeg, float yawDeg, float rollDeg, float *outQuat)
{
    // Global constant for degrees-to-radians conversion (likely M_PI/180 = 0.017453292f)
    const float DEG_TO_RAD = DAT_00e2cd54;

    float radPitch = DEG_TO_RAD * pitchDeg;
    float radYaw   = DEG_TO_RAD * yawDeg;
    float radRoll  = DEG_TO_RAD * rollDeg;

    // sin and cos functions (fast approximations, addresses 0x00b99fcb and 0x00b99e20)
    float sinPitch = sin(radPitch);   // FUN_00b99fcb
    float cosPitch = cos(radPitch);   // FUN_00b99e20
    float sinYaw   = sin(radYaw);
    float cosYaw   = cos(radYaw);
    float sinRoll  = sin(radRoll);
    float cosRoll  = cos(radRoll);

    // Precompute 1 - sin/cos (DAT_00e44564 is known to be 1.0f)
    float oneMinusSinPitch = 1.0f - sinPitch;
    float oneMinusCosPitch = 1.0f - cosPitch;

    // Quaternion components in XYZW order
    outQuat[0] = cosPitch * sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
    outQuat[1] = oneMinusCosPitch * sinYaw * sinRoll + cosYaw * sinPitch * cosRoll;
    outQuat[2] = oneMinusSinPitch * sinYaw * cosRoll + cosYaw * cosPitch * sinRoll;
    outQuat[3] = sinPitch * sinYaw * sinRoll + cosYaw * cosPitch * cosRoll;
}