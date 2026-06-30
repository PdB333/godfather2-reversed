// FUNC_NAME: lerpVector3 (utility function for 3-component linear interpolation, preserves 4th component)
// Address: 0x00427140
// Performs out = src + scale * dir for first three components, leaves out[3] unchanged.
void lerpVector3(float* src, float* dir, float scale, float* out)
{
    float dirY = dir[1];
    float dirZ = dir[2];
    float dirW = dir[3];        // potentially unused in 3D; preserved for alignment
    float srcY = src[1];
    float srcZ = src[2];
    float srcW = src[3];
    float originalOutW = out[3]; // save original fourth component

    out[0] = scale * dir[0] + src[0];
    out[1] = scale * dirY + srcY;
    out[2] = scale * dirZ + srcZ;
    out[3] = originalOutW;       // preserve original w (e.g., homogeneous coordinate or quaternion component)
}