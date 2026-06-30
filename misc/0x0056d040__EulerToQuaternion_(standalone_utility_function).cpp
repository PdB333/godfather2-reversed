// FUNC_NAME: EulerToQuaternion (standalone utility function)
// Address: 0x0056d040
// Converts three Euler angles (in degrees, passed as yaw, pitch, roll) 
// to a quaternion (x,y,z,w) stored in outQuat[4].
// Uses external sin/cos functions (FUN_00b99fcb = sin, FUN_00b99e20 = cos)
// and global constants kDegToRad (0x00e2cd54) and kOne (0x00e44564 = 1.0f).

void EulerToQuaternion(float yaw, float pitch, float roll, float* outQuat)
{
    // Convert degrees to radians
    yaw   = kDegToRad * yaw;
    pitch = kDegToRad * pitch;
    roll  = kDegToRad * roll;

    // Compute sin and cos for each angle
    double dTmp;
    float  sinYaw, cosYaw;
    float  sinPitch, cosPitch;
    float  sinRoll, cosRoll;

    // yaw
    dTmp = (double)yaw;
    sinFunc(&dTmp);  // sin(yaw) – function returns double via dTmp
    sinYaw = (float)dTmp;
    dTmp = (double)yaw;
    cosFunc(&dTmp);  // cos(yaw)
    cosYaw = (float)dTmp;

    // pitch
    dTmp = (double)pitch;
    sinFunc(&dTmp);  // sin(pitch)
    sinPitch = (float)dTmp;
    dTmp = (double)pitch;
    cosFunc(&dTmp);  // cos(pitch)
    cosPitch = (float)dTmp;

    // roll
    dTmp = (double)roll;
    sinFunc(&dTmp);  // sin(roll)
    sinRoll = (float)dTmp;
    dTmp = (double)roll;
    cosFunc(&dTmp);  // cos(roll)
    cosRoll = (float)dTmp;

    // Build quaternion components (order: x, y, z, w)
    // Derived from the decompiled arithmetic:
    float oneMinusSinYaw = kOne - sinYaw;

    outQuat[0] = oneMinusSinYaw * cosPitch * sinRoll + sinPitch * cosYaw * cosRoll;
    outQuat[1] = sinYaw * cosPitch * cosRoll + sinPitch * cosYaw * sinRoll;
    outQuat[2] = oneMinusSinYaw * sinPitch * cosRoll + cosPitch * sinYaw * sinRoll;
    outQuat[3] = sinYaw * sinPitch * sinRoll + cosPitch * cosYaw * cosRoll;
}