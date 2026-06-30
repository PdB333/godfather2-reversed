// FUNC_NAME: Math::computeQuaternionFromEulerAngles
void Math::computeQuaternionFromEulerAngles(float pitch, float yaw, float roll, float *outQuaternion)
{
    // Constants: likely PI/180 or similar conversion factor
    float halfPitch = DAT_00e2cd54 * pitch;  // pitch * 0.5f
    float halfYaw = DAT_00e2cd54 * yaw;      // yaw * 0.5f
    float halfRoll = DAT_00e2cd54 * roll;    // roll * 0.5f

    // Compute sin/cos for half angles
    double dVar7;
    
    dVar7 = (double)halfPitch;
    FUN_00b99fcb();  // sin(halfPitch)
    float sinHalfPitch = (float)dVar7;
    
    dVar7 = (double)halfPitch;
    FUN_00b99e20();  // cos(halfPitch)
    float cosHalfPitch = (float)dVar7;
    
    dVar7 = (double)halfYaw;
    FUN_00b99fcb();  // sin(halfYaw)
    float sinHalfYaw = (float)dVar7;
    
    dVar7 = (double)halfYaw;
    FUN_00b99e20();  // cos(halfYaw)
    float cosHalfYaw = (float)dVar7;
    
    dVar7 = (double)halfRoll;
    FUN_00b99fcb();  // sin(halfRoll)
    float sinHalfRoll = (float)dVar7;
    
    dVar7 = (double)halfRoll;
    FUN_00b99e20();  // cos(halfRoll)
    float cosHalfRoll = (float)dVar7;

    // Compute quaternion components (w, x, y, z)
    // Using standard formula: q = qRoll * qPitch * qYaw (or similar order)
    float cosPitchCosRoll = cosHalfPitch * cosHalfRoll;
    float sinPitchSinRoll = sinHalfPitch * sinHalfRoll;
    
    outQuaternion[0] = cosPitchCosRoll * cosHalfYaw + sinPitchSinRoll * sinHalfYaw;  // w
    outQuaternion[1] = sinHalfPitch * cosHalfRoll * cosHalfYaw + cosHalfPitch * sinHalfRoll * sinHalfYaw;  // x
    outQuaternion[2] = cosPitchCosRoll * sinHalfYaw + sinPitchSinRoll * cosHalfYaw;  // y
    outQuaternion[3] = sinHalfPitch * cosHalfRoll * sinHalfYaw + cosHalfPitch * sinHalfRoll * cosHalfYaw;  // z
}