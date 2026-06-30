//FUNC_NAME: applyLateralForce
// Function address: 0x006c4dc0
// Applies a lateral force (perpendicular to forward direction) scaled by a factor to a velocity/force vector.
// Uses global rotation data (quaternion at 0x00d5780c) to compute the right direction.

void applyLateralForce(float *steeringFactor, float *velocity)
{
    float fVar1;
    float fVar2;
    // Matrix/quaternion conversion temporary variables
    undefined4 matrixData[4]; // local_6c, local_68, local_64, local_60? Actually layout is messy
    undefined4 local_50[3];   // part of matrix
    float forwardX, forwardZ; // local_30, local_28
    float rightDir[3];        // local_60, local_5c, local_58
    undefined4 zero1, zero2, zero3;
    undefined4 globalQuat;    // _DAT_00d5780c

    zero1 = 0;
    zero2 = 0;
    zero3 = 0;
    globalQuat = _DAT_00d5780c; // Global quaternion representing orientation

    // Convert quaternion to matrix (or initialize identity)
    convertQuaternionToMatrix(&matrixData, 0);
    // Transform vector (0,0,1?) through matrix to get forward direction
    transformVector(matrixData[1], matrixData[0], matrixData[2], local_50);
    // Extract forward x and z components (ignoring y)
    forwardX = local_30; // from local_50? Actually local_30 is from stack, likely from transform result
    forwardZ = local_28;

    // Build a 2D forward vector (x, 0, z)
    rightDir[0] = forwardX;
    rightDir[1] = 0.0f;
    rightDir[2] = forwardZ;
    rightDir[3] = 0; // padding? Actually local_54 = 0

    // Normalize the forward vector
    normalizeVector(&rightDir, &rightDir);

    // Rotate forward vector by -90 degrees around Y to get right direction
    // Cross product with (0,0,0) is not standard; this is a manual rotation:
    // new_x = -old_z, new_y = 0, new_z = old_x
    fVar1 = rightDir[1] * 0.0f; // = 0
    fVar2 = fVar1 - rightDir[2]; // = -rightDir[2]
    rightDir[1] = rightDir[2] * 0.0f - rightDir[0] * 0.0f; // = 0
    rightDir[2] = rightDir[0] - fVar1; // = rightDir[0]
    rightDir[3] = 0; // local_54 = 0
    rightDir[0] = fVar2; // = -rightDir[2] (original)

    // Normalize the right direction
    normalizeVector(&rightDir, &rightDir);

    // Apply scaled lateral force to velocity
    velocity[0] += rightDir[0] * (*steeringFactor);
    velocity[1] += rightDir[1] * (*steeringFactor);
    velocity[2] += rightDir[2] * (*steeringFactor);

    return;
}