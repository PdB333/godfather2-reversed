// FUNC_NAME: BoneBlendWeights::getWeight
float __thiscall BoneBlendWeights::getWeight(int this, uint boneIndex, int extraSlotOffset, bool useTargetWeights)
{
    // boneIndex is a byte, limited to 0-17 (0x12 = 18 is sentinel)
    if (boneIndex == 0x12) {
        return 0.0f;
    }

    // Two arrays of floats, each with stride 2 floats per bone (e.g., two weights per bone).
    // Base float indices: 0x5ce (1486) for current weights, 0x60e (1550) for target weights.
    // Access: this + (extraSlotOffset + baseFloatIndex + boneIndex * 2) * sizeof(float)
    if (useTargetWeights) {
        return *(float *)(this + (extraSlotOffset + 0x60e + boneIndex * 2) * 4);
    } else {
        return *(float *)(this + (extraSlotOffset + 0x5ce + boneIndex * 2) * 4);
    }
}