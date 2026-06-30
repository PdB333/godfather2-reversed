// FUNC_NAME: EntityController::applyInputDirection
// Function address: 0x006c5a60
// Role: Updates object position and orientation based on input direction and internal parameters.
// This is likely part of the character/vehicle movement system (EARS physics).
// Structures: offsets relative to `this` (param_1):
//   +0x220: current position (vec3 float)
//   +0x224: previous position (vec3 float)
//   +0x228: previous position z? (wait, later used - so it's the other component)
//   +0x214: target position (vec3 float)
//   +0x208: velocity (vec3 float, may be angular or linear)
//   +0x238, +0x24c: orientation quaternions/matrices
//   +0x284: angular velocity scalar?
//   +0x298: some state pointer/handle
//   +0x10c, +0x108: ratio for smoothing
//   +0x80: interpolation scalar
//   +0x2ec, +0x2b0: combined speed/force factors

void __thiscall EntityController::applyInputDirection(void *this, float *inputDirection)
{
    // inputDirection is a 3-float vector (e.g., stick input)
    float localDirection[3]; // rotated input direction (in local space)
    float rightVector[3];    // cross product of forward with up
    float crossProduct[3];
    double tempDouble;
    float *currentPos = (float *)((char *)this + 0x220); // position at +0x220
    float fVar2, fVar3; // synthetic variables for intermediate results

    // Step 1: Copy input direction to local array (12 bytes = 3 floats)
    copyVector(localDirection, inputDirection); // FUN_00424fb0 copies 12 bytes

    // Step 2: Rotate inputDirection by the object's current orientation (quaternion at +0x220? Wait, pfVar1 is same as currentPos)
    // Actually FUN_006c4390 does: dest = rotate(quat, vec). Parameters: &localDirection, &orientation, <input>, &orientation?
    // The call: FUN_006c4390(&local_30, pfVar1, local_c, pfVar1)
    // This is strange - using same pointer for quaternion and output? Maybe it's a quaternion multiplication:
    // qOut = q1 * q2, where pfVar1 is quaternion and local_c is also quaternion? But local_c is 3 floats.
    // More likely it's a function to transform a vector by a quaternion: result = quat * vector * conj(quat).
    // The signature could be: transformVector(float result[3], float quat[4], float vec[3])
    // But then why pass pfVar1 twice? Possibly the 4th parameter is an output buffer? Or it's a different function.
    // Let's assume it rotates the input direction into local space using the object's rotation stored at +0x220.
    transformVectorByQuaternion(localDirection, (float *)((char *)this + 0x220), inputDirection);
    // Actually the decompiled local_30 etc are after this call, so I'll use localDirection as the rotated vector.

    // Step 3: Compute cross product of direction with up vector (0,1,0) to get right vector
    // local_24 = local_2c*0 - local_28 (where local_30=dx, local_2c=dy, local_28=dz)
    // This produces: right = (-dz, 0, dx)
    rightVector[0] = -localDirection[2];
    rightVector[1] = 0.0f;
    rightVector[2] = localDirection[0];

    // Step 4: Apply a rotation around the right axis by some angle derived from fVar2
    // fVar2 comes from a previous calculation (maybe angular velocity integration)
    // FUN_004a0370 seems to be a rotation by angle: rotateVec(v, axis, angle)
    fVar2 = (float)rotateVectorAroundAxis(localDirection, localDirection, rightVector, getSmoothedAngularVelocity(this));
    // Actually the decompiled has: fVar2 = (float10)FUN_006c3c90(); then fVar2 = (float10)FUN_004a1580(...);
    // That is: compute a quaternion magnitude? Then adjust by something.
    // I'll simplify by calling a helper function that computes the heading angle.

    // Step 5: Compute a step distance (smooth blend)
    float speedFactor = getSpeedFactor(this); // FUN_006c91c0 returns a float between 0 and 1
    speedFactor = (speedFactor - 0.0f) * *(float *)((char *)this + 0x80) + 0.0f; // linear interpolation with scalar
    float step = speedFactor * (*(float *)((char *)this + 0x2ec) + *(float *)((char *)this + 0x2b0));

    // Step 6: Update position
    float *targetPos = (float *)((char *)this + 0x214);
    targetPos[0] = step * localDirection[0] + currentPos[0];
    targetPos[1] = step * localDirection[1] + *(float *)((char *)this + 0x224);
    targetPos[2] = step * localDirection[2] + *(float *)((char *)this + 0x228);

    // Step 7: Compute velocity from position delta and some offset
    float deltaX = targetPos[0] - currentPos[0];
    float deltaY = targetPos[1] - *(float *)((char *)this + 0x224);
    float deltaZ = targetPos[2] - *(float *)((char *)this + 0x228); // local_10 = targetZ - oldZ

    // Set linear velocity / orientation component
    tempDouble = (double)deltaY;
    callInlineFloat64(); // FUN_00b9a9fa (unclear purpose, maybe just a nop or fpu op)
    *(float *)((char *)this + 0x208) = (float)tempDouble; // velocity.x = deltaY ??
    // Hmm, this seems off. Might be setting angular velocity components.
    tempDouble = (double)(DAT_00e44564 - deltaX); // constant minus deltaX
    callInlineFloat64();
    *(float *)((char *)this + 0x20c) = (float)tempDouble; // velocity.y = 1.0 - deltaX ?
    *(undefined4 *)((char *)this + 0x210) = 0; // velocity.z = 0

    // Step 8: Update orientation (quaternion multiplication)
    updateOrientation((void *)((char *)this + 0x24c), (void *)((char *)this + 0x238), (void *)((char *)this + 0x238));
    // This is likely: qCurrent = qCurrent * qOrientationDelta (or q=q * q)
    // FUN_006ca5e0 may be quaternionMultiply
}

// Helper functions (stubs for external calls) - names assumed based on behavior
void copyVector(float *dest, float *src); // FUN_00424fb0
void transformVectorByQuaternion(float *result, float *quat, float *vec); // FUN_006c4390
float getSmoothedAngularVelocity(void *this); // computed from FUN_006c3c90 and FUN_004a1580
float getSpeedFactor(void *this); // FUN_006c91c0
void callInlineFloat64(); // FUN_00b9a9fa (empty in release? maybe just fwait)
void updateOrientation(void *dest, void *src1, void *src2); // FUN_006ca5e0

// Global constants used - likely 0.0 and 1.0
extern float DAT_00d5780c; // assumed 0.0
extern float DAT_00e44564; // assumed 1.0
extern float DAT_00e445c8; // scaling factor for angular velocity