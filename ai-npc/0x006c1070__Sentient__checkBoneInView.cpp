// FUNC_NAME: Sentient::checkBoneInView
int Sentient::checkBoneInView(int* param_1)
{
    int* this = param_1;
    int boneIndex;
    float boneTransform[5]; // 20 bytes: probably position (3) + quaternion (4?) but decompiler says 20 bytes
    float distance;
    void* singleton = FUN_00471610(); // returns pointer to some global (e.g., CameraManager or PlayerManager)
    // The decompiler butchered the next line; likely reading a float from singleton+0x30
    float viewOffset = *(float*)((char*)singleton + 0x30); // originally misinterpreted as 64-bit value
    // The globals are likely camera FOV or near/far plane constants
    float adjustedDistance = ((boneTransform[0] - viewOffset) - _DAT_00d5ef5c) * _DAT_00d5ef58;
    if ((0.0f < adjustedDistance) && (adjustedDistance < _DAT_00d5780c))
    {
        // Condition is true
    }
    // Both branches return the same pointer; possibly a decompilation artifact
    return (int)((char*)singleton + 0x30);
}