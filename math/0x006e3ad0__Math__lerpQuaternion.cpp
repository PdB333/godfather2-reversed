// FUNC_NAME: Math::lerpQuaternion
void __fastcall lerpQuaternion(float *outQuat, float *quatA, float *quatB, float t)
{
    // outQuat is passed in EAX (in_EAX), quatA in param_2, quatB in param_3, t in param_4
    // Quaternions are stored as [x, y, z, w] (4 floats each)
    
    float ax = quatA[0];
    float ay = quatA[1];
    float az = quatA[2];
    float aw = quatA[3];
    
    float bx = quatB[0];
    float by = quatB[1];
    float bz = quatB[2];
    float bw = quatB[3];
    
    // Store the original w component of output (preserved from previous value)
    float savedW = outQuat[3];
    
    // Linear interpolation of each component
    outQuat[0] = (bx - ax) * t + ax;
    outQuat[1] = (by - ay) * t + ay;
    outQuat[2] = (bz - az) * t + az;
    outQuat[3] = (bw - aw) * t + aw;
    
    // Restore the original w component (likely a bug or intentional for some purpose)
    outQuat[3] = savedW;
    
    return;
}