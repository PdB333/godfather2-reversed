// FUNC_NAME: AnimationBone::applyTransform
void AnimationBone::applyTransform(float* position, const float* quaternionXYZ)
{
    // Input position
    float posX = position[0];
    float posY = position[1];
    float posZ = position[2];

    // Bone parameters (offsets: +0x104 blendFactor, +0x108 scaleFactor)
    float blendFactor = *(float*)((int)this + 0x104);
    float scaleFactor = *(float*)((int)this + 0x108);

    // Build full quaternion: xyz from parameter, w from global constant
    float qx = quaternionXYZ[0];
    float qy = quaternionXYZ[1];
    float qz = quaternionXYZ[2];
    float qw = *(float*)0x00d5780c; // global quaternion w component

    // Temporary quaternion array (4 floats)
    float quat[4] = { qx, qy, qz, qw };

    // Work buffer for rotation helper (76 bytes, may hold matrix or intermediate)
    char buffer[76];
    float rotated[3]; // output vector after rotation

    // Call unknown helper functions (likely quaternion normalization/conjugate)
    FUN_00471610(); // possibly normalize quaternion?
    FUN_006e3b00(); // possibly conjugate?

    // Rotate the original position by the quaternion into rotated[]
    FUN_0056b420(buffer, quat, rotated);

    // Blend between rotated and original, then scale
    float blendScale = *(float*)0x00e514ac; // global blend interpolation scale

    float difX = (rotated[0] - blendFactor * posX) * blendScale;
    float difY = (rotated[1] - blendFactor * posY) * blendScale;
    float difZ = (rotated[2] - blendFactor * posZ) * blendScale;

    position[0] = scaleFactor * (difX + blendFactor * posX);
    position[1] = scaleFactor * (difY + blendFactor * posY);
    position[2] = scaleFactor * (difZ + blendFactor * posZ);
}