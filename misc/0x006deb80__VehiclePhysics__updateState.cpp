// FUNC_NAME: VehiclePhysics::updateState
// Address: 0x006deb80
// This function appears to update the physics state of a vehicle or character.
// It takes input positions (param_3, param_4), output position (param_5), and various parameters.
// It computes interpolated positions, applies forces, and integrates the state.

void __thiscall VehiclePhysics::updateState(
    int thisPtr,                    // +0x00: this pointer
    undefined4 param2,              // +0x04: some identifier (e.g., transform index)
    float* inputPosA,               // +0x08: first input position (3 floats)
    float* inputPosB,               // +0x0C: second input position (3 floats)
    float* outputPos,               // +0x10: output position (3 floats)
    undefined4 param6,              // +0x14: unknown
    undefined4 param7,              // +0x18: unknown
    undefined8* outputState,        // +0x1C: output state (8 bytes, likely position + something)
    float* outputVel,               // +0x20: output velocity (3 floats)
    float* outputVel2,              // +0x24: second output velocity (3 floats)
    float* param11,                 // +0x28: some interpolated value
    undefined4 param12,             // +0x2C: unknown
    float* timeStepOut,             // +0x30: output time step
    byte* flagOut,                  // +0x34: output flag (0 or 1)
    int* param15,                   // +0x38: pointer to int (written with global)
    int* stateArray                 // +0x3C: pointer to state array (many ints)
)
{
    int iVar1;
    undefined8 uVar2;
    uint uVar3;
    float* pfVar4;
    int* piVar5;
    byte bVar6;
    int iVar7;
    undefined8* puVar8;
    float10 fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    double dVar13;
    undefined8 local_24;
    float local_1c;
    undefined8 local_18;
    float local_10;
    float local_c;
    float local_8;
    float local_4;

    // Initialize param15 with a global constant (likely some ID or time)
    *param15 = _DAT_00d5780c;

    // Determine offset for time step calculation
    if (*stateArray == 0) {
        iVar7 = 0;
    } else {
        iVar7 = *stateArray + -0x48; // -72
    }

    // Get time step from some function
    fVar9 = (float10)FUN_006dd660(iVar7);
    pfVar4 = timeStepOut;
    fVar12 = DAT_00d5efa0; // Some constant
    param15 = (int*)(float)fVar9;
    *timeStepOut = (float)fVar9;

    // Check a flag from this+0x2d0 structure at offset 0x8e3
    bVar6 = *(byte*)(*(int*)(thisPtr + 0x2d0) + 0x8e3) & 1;
    if (bVar6 == 0) {
        fVar10 = (float)stateArray[0x21]; // stateArray[33]
    } else {
        fVar10 = (float)stateArray[0x57]; // stateArray[87]
    }

    // Interpolate fVar10 with a factor from this+0x80
    fVar10 = (fVar12 - fVar10) * *(float*)(thisPtr + 0x80) + fVar10;

    // Compute param11 based on flag
    if (bVar6 == 0) {
        *param11 = ((float)stateArray[0x19] - fVar10) * (float)param15 + fVar10;
    } else {
        *param11 = ((float)stateArray[0x57] - fVar10) * (float)param15 + fVar10;
    }

    // Lerp positions and velocities
    FUN_006dd6d0(inputPosA, stateArray, *timeStepOut); // lerp position A
    FUN_006dd900(inputPosB, stateArray, *pfVar4);      // lerp velocity B

    // Compute difference vector between lerped positions
    local_10 = *inputPosB - *inputPosA;
    local_18._4_4_ = inputPosB[1] - inputPosA[1];
    local_18._0_4_ = DAT_00e44564 - (inputPosB[2] - inputPosA[2]); // Some constant minus Z difference

    // Get some transform from param2
    puVar8 = (undefined8*)FUN_00424fb0(&local_c, param2);
    uVar2 = *puVar8;
    local_1c = *(float*)(puVar8 + 1);
    uVar3 = *(uint*)(*(int*)(thisPtr + 0x2d0) + 0x8e0); // Another flag from structure

    local_24._0_4_ = (float)uVar2;
    local_24._4_4_ = (float)((ulonglong)uVar2 >> 0x20);

    // Determine flag based on side of plane
    if ((uVar3 >> 0x18 & 1) == 0) {
        if (0.0 <= local_18._4_4_ * (local_24._4_4_ - inputPosA[1]) +
                   ((float)local_24 - *inputPosA) * (float)local_18 + local_10 * (local_1c - inputPosA[2]))
        {
            *flagOut = 0;
        } else {
            *flagOut = 1;
        }
    } else {
        *flagOut = (byte)(uVar3 >> 0x1d) & 1;
    }

    // Apply gravity or other forces
    if (*stateArray == 0) {
        iVar7 = 0;
    } else {
        iVar7 = *stateArray + -0x48;
    }
    local_24 = uVar2;
    FUN_006dc670(&local_c, inputPosB, iVar7); // Apply gravity to position B
    FUN_006dc730(param5, inputPosB, inputPosA, stateArray, *timeStepOut); // Compute acceleration

    // Compute velocity difference
    uVar2 = *(undefined8*)inputPosA;
    local_10 = inputPosA[2];
    local_18._4_4_ = (float)((ulonglong)uVar2 >> 0x20);
    local_24._4_4_ = param5[1] - local_18._4_4_;
    local_18._0_4_ = (float)uVar2;
    local_24._0_4_ = *param5 - (float)local_18;
    local_1c = param5[2] - local_10;

    dVar13 = (double)(float)local_24;
    local_18 = uVar2;
    FUN_00b9a9fa(); // sqrt? or some math function
    param16 = (int*)(float)dVar13;

    // Get another constant based on flag
    if ((*(byte*)(*(int*)(thisPtr + 0x2d0) + 0x8e3) & 1) == 0) {
        fVar12 = (float)stateArray[6];
    } else {
        fVar12 = (float)stateArray[0x56];
    }
    param15 = (int*)(fVar12 * DAT_00e445c8);

    dVar13 = (double)(float)param16;
    FUN_00b99fcb(); // atan2?
    local_24 = CONCAT44(local_24._4_4_, (float)dVar13);

    dVar13 = (double)(float)param16;
    FUN_00b99e20(); // cos?
    local_24 = (ulonglong)(uint)(DAT_00e44564 - (float)local_24);
    local_1c = DAT_00e44564 - (float)dVar13;

    FUN_004a0370(&local_24, &local_24, &local_c, DAT_00e44564 - (float)param15); // quaternion multiply?

    iVar7 = _DAT_00d5780c;
    bVar6 = *(byte*)(*(int*)(thisPtr + 0x2d0) + 0x8e3) & 1;
    if (bVar6 == 0) {
        fVar12 = ((float)stateArray[0x16] - (float)stateArray[0x1e]) * *timeStepOut + (float)stateArray[0x1e];
    } else {
        fVar12 = (float)stateArray[0x52];
    }
    if (bVar6 == 0) {
        fVar10 = ((float)stateArray[0x15] - (float)stateArray[0x1d]) * *timeStepOut + (float)stateArray[0x1d];
    } else {
        fVar10 = (float)stateArray[0x53];
    }
    if (*flagOut != 0) {
        fVar10 = fVar10 * DAT_00d5ccf8;
    }

    // Compute new position
    fVar11 = local_c * fVar10 + fVar12 * (float)local_24 + (float)local_18;
    local_24._0_4_ = fVar11 - *param5;
    param15 = (int*)stateArray[0x1a];
    param16 = (int*)stateArray[0x22];
    local_24._4_4_ = local_8 * fVar10 + fVar12 * local_24._4_4_ + local_18._4_4_;
    iVar1 = stateArray[0x12];
    local_10 = local_4 * fVar10 + fVar12 * local_1c + local_10;
    local_18 = CONCAT44(local_24._4_4_, fVar11);
    local_24._4_4_ = local_24._4_4_ - param5[1];
    local_1c = local_10 - param5[2];

    // Save old state values
    stateArray[0x1a] = _DAT_00d5780c;
    stateArray[0x22] = iVar7;
    stateArray[0x12] = iVar7;

    DAT_0112a900 = 0; // Global flag

    fVar12 = *timeStepOut;
    bVar6 = *flagOut;
    // Call integration function with many parameters
    FUN_006de000(&local_18, &local_24, param5, param6, param11, param12, stateArray, fVar12, bVar6, &timeStepOut, &flagOut, 0);

    DAT_0112a900 = timeStepOut._0_1_; // Restore global from first byte of timeStepOut (odd)

    // Restore state values
    stateArray[0x1a] = (int)param15;
    stateArray[0x22] = (int)param16;
    stateArray[0x12] = iVar1;

    // Write output state
    *outputState = local_18;
    *(float*)(outputState + 1) = local_10;

    // Compute output velocities
    dVar13 = (double)local_24._4_4_;
    FUN_00b9a9fa();
    fVar12 = DAT_00e44564;
    fVar10 = (float)dVar13 * DAT_00e44748;
    *outputVel = fVar10;
    *outputVel2 = fVar10;

    dVar13 = (double)(fVar12 - (float)local_24);
    FUN_00b9a9fa();
    fVar12 = (float)dVar13 * DAT_00e44748;
    outputVel[1] = fVar12;
    outputVel2[1] = fVar12;

    outputVel[2] = 0.0;
    outputVel2[2] = 0.0;

    return;
}