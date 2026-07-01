// FUNC_NAME: AnimationBlendController::updateBlend
// Address: 0x007f7640
// Role: Updates four quaternion blend targets based on accumulated time and random factor.
// Fields: +0x910 accumulatedTime, +0x914 speedScale, +0x918 duration, +0x91c weight,
//         +0x930-0x93c quat0, +0x940-0x94c quat1, +0x950-0x95c quat2, +0x960-0x96c quat3,
//         +0xaf0 blendActive flag

void __thiscall AnimationBlendController::updateBlend(float deltaTime)
{
    float10 fVar1;
    float fVar2;
    float fVar3;
    float local_40[4]; // 16 bytes
    float local_30[4]; // 16 bytes
    float local_20[4]; // 16 bytes

    // Accumulate time
    this->accumulatedTime += deltaTime;
    float t = this->accumulatedTime;

    if (t < this->duration) {
        // Normalize time
        float normalized = t / this->duration;

        // Apply non-linear mapping
        if (normalized >= DAT_00d71c38) {
            // Reverse interpolation after threshold
            normalized = _DAT_00d5780c - (normalized - DAT_00d71c38) * _DAT_00d5eff0;
        } else {
            normalized = normalized * _DAT_00e446b8;
        }

        // Compute scale factor
        float scale = normalized * normalized * this->speedScale;

        // Build weight vectors (complement and direct)
        FUN_0056d6f0(_DAT_00e44564 - this->weight, local_30); // complement weight
        FUN_0056d6f0(this->weight, local_20);                 // direct weight

        // Blend quat0
        FUN_0056d7b0(scale * _DAT_00e44718, local_40);
        FUN_0056d6b0(local_20, local_40, local_30, &this->quat0);

        // Blend quat1
        FUN_0056d7b0(scale * _DAT_00e44828, local_40);
        FUN_0056d6b0(local_20, local_40, local_30, &this->quat1);

        // Set blend active flag
        FUN_0045ee00(&this->blendActive, 1);

        // Random factor for additional variation
        fVar1 = (float10)FUN_007ef4c0();
        float rand = (float)fVar1;
        fVar3 = rand;

        // Build random-weighted vectors
        FUN_0056d6f0(-(rand * this->weight), local_30);
        FUN_0056d6f0(this->weight * rand, local_20);

        // Blend quat2 with random
        FUN_0056d7b0(rand * scale * _DAT_00e44828, local_40);
        FUN_0056d6b0(local_20, local_40, local_30, &this->quat2);

        // Complement random
        float complement = _DAT_00d5780c - rand;
        fVar3 = complement;

        FUN_0056d6f0(_DAT_00e44564 - this->weight * complement, local_30);
        FUN_0056d6f0(this->weight * complement, local_20);
        FUN_0056d7b0(complement * scale * _DAT_00e44828, local_40);
        FUN_0056d6b0(local_20, local_40, local_30, &this->quat3);
    } else {
        // Reset all quaternions to identity (1,0,0,0)
        this->quat0.x = 0.0f;
        this->quat0.y = 0.0f;
        this->quat0.z = 0.0f;
        this->quat0.w = _DAT_00d5780c; // 1.0

        this->quat1.x = 0.0f;
        this->quat1.y = 0.0f;
        this->quat1.z = 0.0f;
        this->quat1.w = _DAT_00d5780c;

        // Deactivate blend
        FUN_0045ee00(&this->blendActive, 0);

        this->quat2.x = 0.0f;
        this->quat2.y = 0.0f;
        this->quat2.z = 0.0f;
        this->quat2.w = _DAT_00d5780c;

        this->quat3.x = 0.0f;
        this->quat3.y = 0.0f;
        this->quat3.z = 0.0f;
        this->quat3.w = _DAT_00d5780c;
    }
}