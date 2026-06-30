// FUNC_NAME: MathUtils::lerpQuaternion
void __thiscall lerpQuaternion(int this, int other, float t)
{
    float* thisQuat = *(float**)(this + 8);   // +0x8: pointer to quaternion (x, y, z, w)
    float* otherQuat = *(float**)(other + 8); // +0x8: pointer to quaternion (x, y, z, w)
    float* resultQuat = *(float**)(this + 8); // +0x8: pointer to output quaternion (x, y, z, w)
    
    // Linear interpolation of quaternion components
    resultQuat[0] = (otherQuat[0] - thisQuat[0]) * t + thisQuat[0]; // x
    resultQuat[1] = (otherQuat[1] - thisQuat[1]) * t + thisQuat[1]; // y
    resultQuat[2] = (otherQuat[2] - thisQuat[2]) * t + thisQuat[2]; // z
    resultQuat[3] = (otherQuat[3] - thisQuat[3]) * t + thisQuat[3]; // w
}