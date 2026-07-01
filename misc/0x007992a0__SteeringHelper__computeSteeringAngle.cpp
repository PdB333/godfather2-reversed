// FUNC_NAME: SteeringHelper::computeSteeringAngle
// Function address: 0x007992a0
// Clamps a steering angle to the maximum allowed and applies it to the vehicle.
// Takes current steering input (param_2), max steering angle (param_3), a multiplier (param_4),
// output angle (param_5), and a direction flag (param_6: -1, 0, or 1 for deadzone compensation).
float10 __thiscall SteeringHelper::computeSteeringAngle(
    int *this,                    // this pointer (likely a vehicle steering controller)
    float inputAngle,             // param_2: raw desired steering angle (relative to vehicle forward?)
    float maxSteeringAngle,       // param_3: maximum allowed steering angle (before multiplying by param_4)
    float multiplier,             // param_4: scaling factor for maxSteeringAngle
    float *outAngle,              // param_5: output clamped angle
    int directionFlag             // param_6: -1 = left, 0 = center, 1 = right (for deadzone logic)
)
{
    char cVar1;
    unsigned int *puVar2;
    int iVar3;
    unsigned int *puVar4;
    bool bVar5;
    bool bVar6;
    float10 fVar7;
    float fVar8;
    double dVar9;
    float adjustedAngle;          // local_58: working copy of adjusted angle
    float matrix[16];             // local_50[0..15]: 4x4 matrix (camera or vehicle transform)
    float forwardX;               // local_30: extracted forward vector x component

    // Get a matrix (likely the camera's view matrix or vehicle's world transform)
    puVar2 = (unsigned int *)FUN_00471610();  // returns pointer to 16 floats (matrix)
    maxSteeringAngle = maxSteeringAngle * multiplier;  // actual maximum steering angle
    puVar4 = (unsigned int *)matrix;
    for (iVar3 = 16; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar4 = puVar4 + 1;
    }
    // Extract the forward x component from the matrix (matrix[12] in row-major)
    dVar9 = (double)matrix[12];   // forwardX
    FUN_00b9a9fa();               // unknown, possibly a sin/cos computation or no-op

    // Compute angle difference: inputAngle - (forwardX * someConstant)
    fVar7 = (float10)FUN_006d6350(inputAngle - (float)dVar9 * DAT_00e44748);  // normalize angle
    adjustedAngle = (float)fVar7;  // store as float

    // Deadzone/transition smoothing based on directionFlag
    if (directionFlag < 1) {
        if ((directionFlag < 0) && (0.0 < adjustedAngle)) {
            adjustedAngle = adjustedAngle - DAT_00d5f4b4;  // subtract small epsilon when turning left
        }
        goto LAB_00799342;
    }
    else if (adjustedAngle < 0.0) {
        adjustedAngle = adjustedAngle + DAT_00d5f4b4;  // add small epsilon when turning right
        goto LAB_00799342;
    }

LAB_00799342:
    // Clamp the angle to the maximum steering bounds, considering wrap-around
    if (adjustedAngle < 0.0) {
        // For negative angles, the effective upper bound is (full circle - maxSteeringAngle)
        maxSteeringAngle = DAT_00e44564 - maxSteeringAngle;
        bVar6 = (adjustedAngle == maxSteeringAngle);
        bVar5 = (adjustedAngle < maxSteeringAngle);  // if true, angle is beyond the bound (wrapped)
    }
    else {
        bVar6 = (maxSteeringAngle == adjustedAngle);
        bVar5 = (maxSteeringAngle < adjustedAngle);  // if true, angle exceeds positive bound
    }

    // Apply clamping: if out of bounds, use the bound value
    fVar8 = adjustedAngle;
    if (bVar5 || bVar6) {
        fVar8 = maxSteeringAngle;
    }
    *outAngle = fVar8;

    // Normalize the output angle again
    fVar7 = (float10)FUN_006d6350(*outAngle);
    *outAngle = (float)fVar7;

    // Check some condition (e.g., is vehicle driving, or if angle is within range)
    cVar1 = FUN_00481660();  // returns char, possibly a boolean
    if (
        ((cVar1 == '\0') || (DAT_00d5f168 < *outAngle)) || 
        (*outAngle < DAT_00d6a5c8)
       ) {
        // Call a virtual function (likely to apply steering torque or set steering)
        // +0x60 is the vtable offset for this method
        (**(code **)(*this + 0x60))(&DAT_00d6a4f4, *outAngle * DAT_00e445c8);
    }

    return (float10)adjustedAngle;  // return the raw (unclamped) angle for logging/debugging
}