// FUNC_NAME: AnimationStateManager::interpolatePose
void __thiscall AnimationStateManager::interpolatePose(AnimationBlendBuffer *blendBuffer, int boneIndex)
{
    short sVar1;
    ushort uVar2;
    int iVar3;
    
    // Set blend type (likely matrix/quaternion blend mode)
    blendBuffer->blendType = 7;
    
    // Check if first bone count (offset +0x2a) is valid
    if (*(short *)(this + 0x2a) < 1) {
        // No bones - set identity/empty transform
        blendBuffer->transform1 = 0;      // +0x04
        blendBuffer->transform2 = 0;      // +0x08
        blendBuffer->transform3 = 0;      // +0x0c
        blendBuffer->boneIndex1 = -1;     // +0x10
    }
    else {
        // Get bone data pointer (offset +0x78) and index lookup (offset +0x7c)
        if (*(int *)(this + 0x78) == 0) {
            iVar3 = 0;
        }
        else {
            // Index into bone lookup table (ushort array at +0x7c)
            iVar3 = (uint)*(ushort *)(*(int *)(this + 0x7c) + boneIndex * 2) +
                    *(int *)(this + 0x78);
        }
        blendBuffer->boneDataPtr = iVar3;  // +0x04
        blendBuffer->weight = *(int *)(this + 0x4c);  // +0x08
        blendBuffer->offset1 = *(int *)(this + 0x6c); // +0x0c
        blendBuffer->endFlag1 = 0;         // +0x10
    }
    
    // Second bone batch (offset +0x2c)
    if (*(short *)(this + 0x2c) < 1) {
        blendBuffer->transform4 = 0;       // +0x14
        blendBuffer->boneIndex2 = -1;      // +0x18
    }
    else {
        blendBuffer->transform4 = *(int *)(this + 0x50);  // +0x14
        blendBuffer->boneIndex2 = 0;       // +0x18
    }
    
    // Third bone batch (offset +0x34)
    if (*(short *)(this + 0x34) < 1) {
        blendBuffer->transform5 = 0;       // +0x1c
        blendBuffer->transform6 = 0;       // +0x20
        blendBuffer->transform7 = 0;       // +0x24
        blendBuffer->boneIndex3 = -1;      // +0x28
    }
    else {
        sVar1 = *(short *)(this + 0x38);
        iVar3 = *(int *)(this + 0x60);
        blendBuffer->boneIndex3 = 0;       // +0x28
        blendBuffer->transform5 = sVar1 * boneIndex + iVar3;  // +0x1c
        blendBuffer->transform6 = *(int *)(this + 0x68);      // +0x20
        blendBuffer->transform7 = *(int *)(this + 0x70);      // +0x24
    }
    
    // Fourth bone batch (offset +0x32)
    if (*(short *)(this + 0x32) < 1) {
        blendBuffer->transform8 = 0;       // +0x2c
        blendBuffer->transform9 = 0;       // +0x30
        blendBuffer->transform10 = 0;      // +0x34
        blendBuffer->boneIndex4 = -1;      // +0x38
    }
    else {
        blendBuffer->transform8 = *(int *)(this + 0x5c) + *(short *)(this + 0x36) * boneIndex * 2;  // +0x2c
        blendBuffer->transform9 = *(int *)(this + 100);    // +0x30
        blendBuffer->transform10 = *(int *)(this + 0x74);  // +0x34
        blendBuffer->boneIndex4 = 0;       // +0x38
    }
    
    // Fifth bone batch (offset +0x30)
    if (*(short *)(this + 0x30) < 1) {
        blendBuffer->transform11 = 0;      // +0x3c
        blendBuffer->boneIndex5 = -1;      // +0x40
    }
    else {
        blendBuffer->transform11 = *(int *)(this + 0x54) + *(short *)(this + 0x30) * boneIndex * 0xc;  // +0x3c
        blendBuffer->boneIndex5 = 0;       // +0x40
    }
    
    // Root transform data (offset +0x18)
    blendBuffer->rootTransform = *(int *)(this + 0x58);      // +0x44
    blendBuffer->rootFlag = 0;                                // +0x48
    if (*(short *)(this + 0x18) == 0) {
        blendBuffer->extraData = 0;                           // +0x4c
    }
    else {
        blendBuffer->extraData = *(int *)(this + 0x48);       // +0x4c
    }
    
    // Final section with division (offset +0x2e, +0x24)
    sVar1 = *(short *)(this + 0x2e);
    uVar2 = *(ushort *)(this + 0x24);
    blendBuffer->someFlag = 0;                                // +0x50
    blendBuffer->baseTransform = *(int *)(this + 0x3c);      // +0x54
    // Calculate interpolated position with stride
    blendBuffer->finalPosition = ((int)sVar1 / (int)(uint)uVar2) * boneIndex + *(int *)(this + 0x44);  // +0x58
    return;
}