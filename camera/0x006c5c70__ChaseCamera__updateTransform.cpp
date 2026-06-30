// FUNC_NAME: ChaseCamera::updateTransform
// Function address: 0x006c5c70
// Updates the camera's target position and look-at vector based on input and frame time.
// Uses spring-damper velocity integration and spherical coordinate calculations.

void __fastcall ChaseCamera::updateTransform(Camera* this)
{
    float dt;
    float speed;
    float angle;
    float sinAngle;
    float weight;
    float radius;
    float x, y, z;
    float lookX, lookY, lookZ;

    dt = getDeltaTime(); // FUN_00471610
    springDampVelocity(dt, &this->mInputVelocity.x, &this->mInputVelocity.y, &this->mInputVelocity.z); // FUN_0056c180

    // Forward movement component based on speed and input
    this->mInputVelocity.x = this->mSpeed * 0.016f + this->mInputVelocity.x; // DAT_00e445c8 likely frame time constant (0.016)
    // Note: The decompiler shows DAT_00e445c8 used as multiplier; assuming 0.016 (1/60) for 60 fps

    float temp1 = this->mInputVelocity.x;
    double d1 = temp1;
    FUN_00b99fcb(); // Possibly double conversion or FPU mode set
    double d2 = temp1;
    FUN_00b99e20(); // Another FPU operation

    float diff1 = 1.0f - (float)d1; // DAT_00e44564 is likely 1.0f
    float diff2 = 1.0f - (float)d2;

    // Angle integration with noise
    float noise = getNoise(); // FUN_006c3c90
    angle = (noise + this->mAngleOffset) * 0.016f; // DAT_00e445c8 again
    sinAngle = fsin(angle);

    radius = angle * diff1; // Component of orbit
    float height = getHeightOffset(); // FUN_006c3910(0,0,0)
    this->mHeightOffset = height;

    // Weight for distance interpolation
    weight = smoothStepWeight(*(uint32*)&this->mZoomValue, 0, 1.0f, 1.0f, this->mCurrentDistance / this->mMaxDistance); // FUN_006c91c0
    float clampedWeight = (weight - sGlobalWeightOffset) * this->mWeightScale + sGlobalWeightOffset; // Using _DAT_00d5780c
    float finalRadius = clampedWeight * (this->mExtraOffset + this->mHeightOffset);

    // Compute target position
    this->mTargetPosition.x = finalRadius * radius + this->mBasePosition.x;
    this->mTargetPosition.y = finalRadius * sinAngle + this->mBasePosition.y;
    this->mTargetPosition.z = finalRadius * angle * diff2 + this->mBasePosition.z;

    // Compute look-at vector (normalized? direction to target)
    this->mLookAt.x = sinAngle;
    this->mLookAt.y = 1.0f - radius;
    this->mLookAt.z = 0.0f;

    // Copy results to output transformation
    *(Vector2*)(this->mOutputPos) = *(Vector2*)(&this->mTargetPosition);
    *(Vector2*)(this->mOutputLookAt) = *(Vector2*)(&this->mLookAt);
    this->mOutputPos.z = this->mTargetPosition.z;
    this->mOutputLookAt.z = this->mLookAt.z;
}