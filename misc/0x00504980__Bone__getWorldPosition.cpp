// FUNC_NAME: Bone::getWorldPosition
void __thiscall Bone::getWorldPosition(float *outPos)
{
    // Access thread-local storage for current frame transform data
    // FS:[0x2C] -> pointer to TLS array, then dereference to get base pointer
    // +0x80 is offset to transform array, indexed by this->boneIndex (+0x08)
    float *src = (float *)(*(int *)(**(int **)(__readfsdword(0x2C) + 8) + 0x80 + *(int *)(this + 8));

    // Copy 4 floats (position + w component)
    outPos[0] = src[0];
    outPos[1] = src[1];
    outPos[2] = src[2];
    outPos[3] = src[3];

    // Get parent transform or entity pointer at +0x20
    int parentObj = *(int *)(this + 0x20);

    // Check flags at parentObj+0x14 (bit 1 and 2) – if not set, add parent's world position
    if ((*(byte *)(parentObj + 0x14) & 6) == 0)
    {
        outPos[0] += *(float *)(parentObj + 0x30);
        outPos[1] += *(float *)(parentObj + 0x34);
        outPos[2] += *(float *)(parentObj + 0x38);
    }
}