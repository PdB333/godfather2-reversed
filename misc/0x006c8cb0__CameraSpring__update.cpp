// FUNC_NAME: CameraSpring::update

void __thiscall CameraSpring::update(float dt, float springStiffness, float targetOffset, float damping, const Vector3& fromPoint, Vector3& toPoint, Vector3& outVelocity)
{
    float fVar1;
    float fVar2;
    double dVar3;
    float fVar4;
    Vector3 diff; // local_38, local_34, local_30
    Vector3 crossResult; // local_2c, local_28, local_24
    Vector3 normalized; // local_20, local_1c, local_18 reused
    Vector3 temp; // reusing
    float tempFloat;

    // Global constants: g_dtScale, g_one, g_velocityScale, g_useAltFormula
    // DAT_00e445c8 likely time scale factor
    // DAT_00e44564 likely 1.0f
    // DAT_0112a7a4 is a toggle flag

    if (DAT_0112a7a4 == '\0') {
        fVar4 = dt * targetOffset * DAT_00e445c8;
    } else {
        fVar4 = DAT_00e44564 - dt * targetOffset * DAT_00e445c8;
    }

    // Update spring state (position at +0x8c, velocity at +0x90)
    fVar1 = *(float *)(this + 0x8c) - fVar4;
    fVar2 = (fVar1 * damping + *(float *)(this + 0x90)) * springStiffness;
    dVar3 = (double)(DAT_00e44564 - springStiffness * damping);
    FUN_00b9be2b(); // likely a math helper (e.g., saturation)
    fVar4 = (fVar2 + fVar1) * (float)dVar3 + fVar4;
    *(float *)(this + 0x8c) = fVar4;
    *(float *)(this + 0x90) = (*(float *)(this + 0x90) - fVar2 * damping) * (float)dVar3;

    // Compute difference: toPoint - fromPoint
    diff.y = toPoint.y - fromPoint.y;
    diff.x = toPoint.x - fromPoint.x;
    diff.z = toPoint.z - fromPoint.z;

    // Normalize diff? But we have a cross product computed first
    normalized.z = 0.0f;
    // local_14 is set to 0, likely unused
    Vector3 crossInput = diff; // copy
    FUN_0056afa0(&crossInput, &normalized); // normalize crossInput? Actually it takes two pointers, result in second? Or both? We'll assume normalize a vector

    // Cross product with (0,0,1) - plane perpendicular?
    crossResult.x = normalized.y * 0.0f - normalized.z;
    crossResult.y = normalized.z * 0.0f - normalized.x * 0.0f; // simplified to 0
    crossResult.z = normalized.x - normalized.y * 0.0f; // simplified to normalized.x

    // Now mix diff and crossResult by fVar4 (the spring output)
    FUN_004a0370(&diff, &diff, &crossResult, fVar4); // likely vector lerp or add? Assuming blends

    // Output new toPoint = fromPoint + blended diff
    toPoint.x = fromPoint.x + diff.x;
    toPoint.y = fromPoint.y + diff.y;
    toPoint.z = fromPoint.z + diff.z;

    // Compute output velocity based on diff.y and diff.x relative to 1.0
    dVar3 = (double)diff.y;
    FUN_00b9a9fa(); // unknown math function
    outVelocity.x = (float)dVar3 * DAT_00e44748; // scale
    dVar3 = (double)(DAT_00e44564 - diff.x);
    FUN_00b9a9fa();
    outVelocity.y = (float)dVar3 * DAT_00e44748;
    outVelocity.z = 0.0f;
}