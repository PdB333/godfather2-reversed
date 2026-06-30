// FUNC_NAME: Bone::update
void __thiscall Bone::update(float dt)
{
    // Thread-local storage pointer to global BoneManager or similar
    BoneManager* boneManager = *(BoneManager**)(__readfsdword(0x2c));
    
    // Check if animation state exists and has data
    if (this->animState != nullptr && this->animState->data != nullptr) {
        resetAnimationFrame(this->parent, 0);
        
        // Calculate index into bone manager's array
        int* baseArray = boneManager->baseArray;
        int index = baseArray[2] + this->animState->offset;
        // Set two uint32 values at computed position (maybe time and animation ID)
        *(uint32_t*)(index + 0x28) = this->animState->someAnimationId;
        *(uint32_t*)(index + 0x2c) = *(uint32_t*)&in_XMM0_Da;  // from XMM0 in assembly
    }
    
    // Timer logic: count down, fire when expires
    if (this->timer > 0.0f) {
        this->timer -= dt;
        if (this->timer <= 0.0f) {
            this->timer = 0.0f;
            
            // Set a flag (bit 0) on the bone's bitfield via manager array
            uint32_t* flagField = (uint32_t*)(boneManager->baseArray[2] + this->boneIndex);
            *flagField |= 1;
            
            // If there is a linked bone, update its state
            if (this->linkedBone != nullptr) {
                if ((this->linkedBone->stateFlags & 0x20000) == 0) {
                    this->linkedBone->stateFlags |= 0x20000;
                    setDirtyFlag();  // Mark something as dirty
                }
                this->linkedBone->stateFlags &= 0xfffbffff;  // Clear bit 0x40000
            }
        }
    }
    
    // Update linked bone's world transform if applicable
    if (this->linkedBone != nullptr && this->linkedBone->someTransformFlag == 0) {
        // Check if either of two conditions hold (related to flags)
        if ((this->parent->flags1 & 0x8000) == 0 ||
            (*(uint32_t*)(boneManager->baseArray[2] + this->boneIndex) & 0x40000000) == 0) {
            // Copy a 4x4 matrix from static identity/transform
            const float* identity = getIdentityMatrix();
            this->linkedBone->worldTransform[0] = identity[0];    // +0x30
            this->linkedBone->worldTransform[1] = identity[1];    // +0x34
            this->linkedBone->worldTransform[2] = identity[2];    // +0x38
            this->linkedBone->worldTransform[3] = identity[3];    // +0x3c
            this->linkedBone->worldTransform[4] = identity[4];    // +0x40
            this->linkedBone->worldTransform[5] = identity[5];    // +0x44
            this->linkedBone->worldTransform[6] = identity[6];    // +0x48
            this->linkedBone->worldTransform[7] = identity[7];    // +0x4c
            this->linkedBone->worldTransform[8] = identity[8];    // +0x50
            this->linkedBone->worldTransform[9] = identity[9];    // +0x54
            this->linkedBone->worldTransform[10] = identity[10];  // +0x58
            this->linkedBone->worldTransform[11] = identity[11];  // +0x5c
            this->linkedBone->worldTransform[12] = identity[12];  // +0x60
            this->linkedBone->worldTransform[13] = identity[13];  // +0x64
            this->linkedBone->worldTransform[14] = identity[14];  // +0x68
            this->linkedBone->worldTransform[15] = identity[15];  // +0x6c
        }
        // Copy parent's animation ID or similar to linked bone
        this->linkedBone->animId = this->parent->animId;  // +0x84 from parent, +0x84 to linked
    }
}