// FUNC_NAME: PhysicsConstraint::applyConstraintForce
void __fastcall PhysicsConstraint::applyConstraintForce(
    undefined4 thisPtr,
    float *constraintAxis,
    float *targetPos,
    int constraintDef,
    float *outputForce)
{
    byte *pbVar4;
    undefined1 *constraintType;
    uint flags;
    float local_30[4];
    float diff[4];
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar1;
    float10 fVar5;

    // Get object data pointer from thread-local storage (TLS) + entity offset
    pbVar4 = (byte *)(*(int *)(**(int **)(*(int *)0x2c + 8) + 8) + *(int *)(unaff_EDI + 0x10));
    
    if ((*pbVar4 & 1) != 0) {
        return;
    }

    constraintType = *(undefined1 **)(unaff_EDI + 0x24);
    
    // Compute difference between target position and current position (quaternion)
    diff[0] = *(float *)(pbVar4 + 0x80) - *targetPos;
    diff[1] = *(float *)(pbVar4 + 0x84) - targetPos[1];
    diff[2] = *(float *)(pbVar4 + 0x88) - targetPos[2];
    diff[3] = *(float *)(pbVar4 + 0x8c) - targetPos[3];

    // Determine constraint axis based on type
    switch(constraintType[1]) {
    case 0: // Use diff as axis
        local_30[0] = diff[0];
        local_30[1] = diff[1];
        local_30[2] = diff[2];
        local_30[3] = diff[3];
        break;
    case 1: // Use provided constraint axis
        local_30[0] = *constraintAxis;
        local_30[1] = constraintAxis[1];
        local_30[2] = constraintAxis[2];
        local_30[3] = constraintAxis[3];
        break;
    case 2: // Use world-space axis (offset 0x50)
        local_30[0] = *(float *)(pbVar4 + 0x50);
        local_30[1] = *(float *)(pbVar4 + 0x54);
        local_30[2] = *(float *)(pbVar4 + 0x58);
        local_30[3] = *(float *)(pbVar4 + 0x5c);
        break;
    case 3: // Use another axis (offset 0x60)
        local_30[0] = *(float *)(pbVar4 + 0x60);
        local_30[1] = *(float *)(pbVar4 + 100);
        local_30[2] = *(float *)(pbVar4 + 0x68);
        local_30[3] = *(float *)(pbVar4 + 0x6c);
        break;
    case 4: // Use axis at offset 0x70
        local_30[0] = *(float *)(pbVar4 + 0x70);
        local_30[1] = *(float *)(pbVar4 + 0x74);
        local_30[2] = *(float *)(pbVar4 + 0x78);
        local_30[3] = *(float *)(pbVar4 + 0x7c);
        break;
    }

    flags = *(uint *)(constraintType + 4); // +0x04 flags field
    
    // Cross product operation if flag 0x4 is set (orient constraint axis)
    if ((flags & 4) != 0) {
        fVar6 = local_30[0] * constraintAxis[1];
        fVar7 = local_30[0] * constraintAxis[2];
        fVar8 = local_30[1] * *constraintAxis;
        local_30[0] = local_30[1] * constraintAxis[2] - local_30[2] * constraintAxis[1];
        local_30[1] = local_30[2] * *constraintAxis - fVar7;
        local_30[2] = fVar6 - fVar8;
    }

    // Normalize the constraint axis
    fVar6 = local_30[2] * local_30[2] + local_30[1] * local_30[1] + local_30[0] * local_30[0];
    if (fVar6 <= DAT_00e2cbe0) {
        fVar6 = 0.0f;
    } else {
        fVar6 = DAT_00e2b1a4 / SQRT(fVar6); // 1 / length
    }

    // Calculate constraint error based on type
    fVar7 = DAT_00e2b1a4; // default 1.0
    switch(*constraintType) {
    case 1: // Distance constraint
        constraintAxis = &diff[0];
    case 5:
        fVar5 = (float10)FUN_004bcfb0(constraintAxis); // likely vector length
        fVar7 = (float)fVar5;
        break;
    case 2: // Dot product with first local axis
        fVar7 = *(float *)(pbVar4 + 0x54) * diff[1] + 
                *(float *)(pbVar4 + 0x58) * diff[2] + 
                diff[0] * *(float *)(pbVar4 + 0x50);
        break;
    case 3: // Dot product with second local axis
        fVar7 = *(float *)(pbVar4 + 100) * diff[1] + 
                *(float *)(pbVar4 + 0x68) * diff[2] + 
                *(float *)(pbVar4 + 0x60) * diff[0];
        break;
    case 4: // Dot product with third local axis
        fVar7 = *(float *)(pbVar4 + 0x74) * diff[1] + 
                *(float *)(pbVar4 + 0x78) * diff[2] + 
                diff[0] * *(float *)(pbVar4 + 0x70);
        break;
    }

    // Apply constraint error bias (offset +0x28)
    fVar7 = fVar7 - *(float *)(constraintType + 0x28);
    
    if (fVar7 == 0.0f) {
        return;
    }

    // Apply error reduction mode
    switch(constraintType[2]) {
    case 0: // Square error
        fVar7 = fVar7 * fVar7;
        break;
    case 2: // Square root
        fVar7 = SQRT(fVar7);
        break;
    case 3: // Square root then reciprocal
        fVar7 = SQRT(fVar7);
    case 4:
        goto LAB_004f36b5;
    case 5: // Square then reciprocal
        fVar7 = fVar7 * fVar7;
LAB_004f36b5:
        fVar7 = DAT_00e2b1a4 / fVar7;
        break;
    }

    // Apply stiffness (offset +0x24) and damping (offset +0x2c)
    fVar7 = *(float *)(constraintType + 0x24) * fVar7;
    fVar8 = fVar7;
    
    if (*(float *)(constraintType + 0x2c) != 0.0f) {
        fVar1 = *(float *)(constraintType + 0x2c);
        fVar8 = DAT_00e44564 - fVar1; // 1.0 - damping
        if ((fVar8 < fVar7) && (fVar8 = fVar7, fVar1 <= fVar7)) {
            fVar8 = fVar1;
        }
    }

    // Apply additional scaling factors from constraint definition
    if ((flags & 8) != 0) {
        fVar8 = *(float *)(constraintDef + 4) * fVar8;
    }
    if ((flags & 0x10) != 0) {
        fVar8 = *(float *)(constraintDef + 8) * fVar8;
    }

    // Apply force to output (quaternion representation)
    outputForce[0] = fVar8 * local_30[0] * fVar6 + outputForce[0];
    outputForce[1] = fVar8 * local_30[1] * fVar6 + outputForce[1];
    outputForce[2] = fVar8 * local_30[2] * fVar6 + outputForce[2];
    outputForce[3] = fVar8 * local_30[3] + outputForce[3];

    return;
}