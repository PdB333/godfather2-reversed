// FUNC_NAME: MathUtils::lerpQuaternion
void __thiscall MathUtils::lerpQuaternion(float *fromQuat, float t, float *toQuat, float *outQuat)
{
    // Linear interpolation between two quaternions (x,y,z,w format)
    // outQuat = fromQuat + t * (toQuat - fromQuat)
    // +0x00: x component
    // +0x04: y component  
    // +0x08: z component
    // +0x0C: w component
    
    float fromX = fromQuat[0];
    float fromY = fromQuat[1];
    float fromZ = fromQuat[2];
    float fromW = fromQuat[3];
    
    float toX = toQuat[0];
    float toY = toQuat[1];
    float toZ = toQuat[2];
    float toW = toQuat[3];
    
    outQuat[0] = (toX - fromX) * t + fromX;
    outQuat[1] = (toY - fromY) * t + fromY;
    outQuat[2] = (toZ - fromZ) * t + fromZ;
    outQuat[3] = (toW - fromW) * t + fromW;
}