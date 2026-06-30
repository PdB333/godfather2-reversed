// FUNC_NAME: VectorMath::applyRotationDeltaToVector
// Function address: 0x006c4dc0
// Applies a small rotation delta to a 3D vector, likely in the XZ plane (around Y axis).
// param_1: pointer to a float scaling factor (rotation angle delta)
// param_2: pointer to 3-float vector to be rotated (modified in-place)

void applyRotationDeltaToVector(float *pAngleScale, float *pVec)
{
    // Local data: quaternion (or matrix) set to identity via FUN_00425060
    float quat[4];             // +0x6c
    float axisOut[3];          // +0x68 (x?), +0x64 (y?), +0x50 (z?) – approximate layout
    float local_30;            // temporary, reused from axis decomposition
    float local_28;            // temporary
    float local_14 = _DAT_00d5780c; // constant (likely 0.0f or identity flag)

    // Initialize identity quaternion (or matrix) – FUN_00425060(quat, 0)
    FUN_00425060(quat, 0);

    // Extract rotation axis from quaternion – FUN_0056b8a0 returns axis and angle
    // Signature: FUN_0056b8a0(&axis.x, quat, &axis.y, &axis.z_angle)
    FUN_0056b8a0(&axisOut[0], quat, &axisOut[1], &axisOut[2]);

    // Reconstruct the axis component (assume axis lies in XZ plane, y=0)
    // After extraction, the axis likely has non-zero x and z, y = 0
    // local_30 and local_28 are parts of axis from output
    float perpVec[3];
    perpVec[0] = local_30;    // axis.x (or from axisOut[0])
    perpVec[1] = 0.0f;
    perpVec[2] = local_28;    // axis.z (or from axisOut[2])

    // Normalize the perpendicular vector – FUN_0056afa0
    FUN_0056afa0(perpVec, perpVec);

    // Apply a 90-degree rotation (cross with (0,1,0)) to get a direction perpendicular to the axis
    float temp = perpVec[0];
    perpVec[0] = -perpVec[2]; // new x = -old z
    perpVec[2] = temp;        // new z = old x
    // y remains 0

    // Normalize again – FUN_0056afa0
    FUN_0056afa0(perpVec, perpVec);

    // Apply the rotation delta: pVec += pAngleScale * (perpVec)
    float scale = *pAngleScale;         // rotation angle delta (in radians?)
    pVec[0] += perpVec[0] * scale;
    pVec[1] += perpVec[1] * scale;     // perpVec[1] is 0, so y unchanged
    pVec[2] += perpVec[2] * scale;
}