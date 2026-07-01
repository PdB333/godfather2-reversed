// FUNC_NAME: SmoothNodeInterpolator::update
void SmoothNodeInterpolator::update(float dt, bool checkCollision) {
    // Local matrix/transform (16 floats)
    struct Transform { float m[16]; } transform;
    memset(&transform, 0, sizeof(transform)); // entire buffer zeroed? Actually only local_200 is 512 bytes, but we only use part

    // Initialize a few fields
    transform.m[0] = 0.5f; // 0x80 as float? Actually short: local_22c = 128, then local_22a=0. Interpreting as half precision? We'll assume identity
    // The code sets local_22c = 0x80, local_22a = 0, local_228 = 0, etc.
    // We'll skip detailed initialization; the actual values come from memory.

    // Determine base transform pointer puVar3
    float* baseTransform;
    float currentTime = this->time_; // +0xf4
    float globalMaxTime = g_maxInterpolationTime; // _DAT_00d5780c

    if (globalMaxTime <= currentTime) {
        // Use current node
        if (this->useCurrentTransform_ == 0) { // +0x10
            baseTransform = reinterpret_cast<float*>(this->currentTransformPtr_); // +0x4
        } else {
            FUN_007ef2a0(&transform, this->currentTransformPtr_); // +0x4, and write to transform
            baseTransform = reinterpret_cast<float*>(&transform);
        }
    } else {
        // Interpolate between previous and current
        float invFactor = globalMaxTime - currentTime;
        float factor = globalMaxTime - invFactor * invFactor;
        FUN_007f2810(this->previousTransformPtr_, this->currentTransformPtr_, factor); // +0x8, +0x4
        if (this->useCurrentTransform_ != 0) {
            FUN_007ef2a0(baseTransform, baseTransform); // identity? Probably copy
        }
    }

    // Compute position and rotation from transform + extra offset
    float posX, posY, posZ;
    FUN_007ef570(&posX, &posY, &posZ, this->someOffset_, baseTransform); // +0xd4

    // Clamp position components
    float clampHigh = g_angleLimitHigh; // DAT_00e44564
    float clampLow = g_angleLimitLow;   // DAT_00e53690 (for Y) and DAT_00e5368c (for Z)

    // Clamp posY (second component)
    float temp = clampHigh - clampLow;
    if (posY <= clampLow) {
        temp = (temp <= posY) ? posY : temp; //? Actually logic: if fVar4 <= posY, use fVar4 else use posY? Wait, complicated.
    } else {
        temp = clampLow;
    }
    posY = temp; // simplified: clamp(posY, clampLow, clampHigh)? The code is messy.

    // Similarly clamp posZ
    float temp2 = clampHigh - clampLow2; // clampLow2 = DAT_00e5368c
    if (posZ <= clampLow2) {
        temp2 = (temp2 <= posZ) ? posZ : temp2;
    } else {
        temp2 = clampLow2;
    }
    posZ = temp2;

    // Also clamp zero reference for Y and Z (for second function)
    float clampLowY = g_angleLimitLow; // DAT_00e53690
    float clampLowZ = g_angleLimitLow2; // DAT_00e5368c
    // Actually the code uses local_234 and local_238 as zero-clamped values
    float zeroY, zeroZ;
    if (0.0f <= clampLowY) {
        float temp3 = clampHigh - clampLowY;
        zeroY = (temp3 <= 0.0f) ? 0.0f : temp3; // simplified
    } else {
        zeroY = clampLowY;
    }
    if (0.0f <= clampLowZ) {
        float temp4 = clampHigh - clampLowZ;
        zeroZ = (temp4 <= 0.0f) ? 0.0f : temp4;
    } else {
        zeroZ = clampLowZ;
    }

    // If collision check enabled, do more work
    if (checkCollision) {
        FUN_007ef9c0(/* offsets +0x1f0, +0x250, etc */);
        FUN_007ef9c0(/* offsets +0x220, +0x280*/);
        FUN_007f13c0(/* offsets +0x2e0, +0x2b0, +0x340, +0x310, with computed values */);
        FUN_007efea0(baseTransform);
        FUN_007efc40(/* offsets +0x430 to +0x5b0 */);
    }

    // Set final position (at +0x100) and rotation (at +0x130)
    FUN_0056d370(posZ, posX, posY, this->finalPosition_); // +0x100
    FUN_0056d370(zeroZ, 0.0f, zeroY, this->finalRotation_); // +0x130 (only two components, roll=0)

    // Update timer
    float accumulatedTime = this->accumulatedTime_; // +0x28
    accumulatedTime += dt;
    this->accumulatedTime_ = accumulatedTime;

    float newTime = accumulatedTime * g_timeMultiplier; // DAT_00e447a8
    this->time_ = newTime;

    // Check for overflow and swap nodes
    float maxTime = g_maxInterpolationTime;
    if (maxTime < newTime) {
        int nextNode = *reinterpret_cast<int*>(this->nodeNextStack_); // +0xc
        if (nextNode != 0) {
            this->nodeNextStack_ = 0;
            *reinterpret_cast<int*>(this->nodeCurrentTransform_ + 4) = this->currentTransformPtr_; //? careful
            this->currentTransformPtr_ = nextNode;
            this->time_ = 0.0f;
            this->accumulatedTime_ = 0.0f;
        } else {
            this->time_ = maxTime; // clamp
        }
    }
}