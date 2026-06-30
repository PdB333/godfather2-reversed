// FUNC_NAME: InputStickManager::processStickInput

// Function at 0x004663a0: Processes a 4D input vector for a given stick index.
// Handles horizontal (x,y) and vertical (z,w) components separately.
// Stores raw magnitudes, processed magnitudes, and difference values used for angle computation.

// Constants (likely loaded from global data)
const float MAX_STICK_MAGNITUDE = DAT_00e2b1a4;
const float DEADZONE_CENTER = DAT_00e44564; // Assumed 0.0f, used as subtractor

// Structure offsets (relative to 'this' pointer)
// +0x16b0: blendFactor (sensitivity/deadzone blend)
// +0x16b8: rawMagnitudes[2] (each 8 bytes: magnitude, angle diff?)
// +0x1738: rawAngleDiffs[2]
// +0x17b8: processedMagnitudes[2]
// +0x1838: processedAngleDiffs[2]

void InputStickManager::processStickInput(byte stickIndex)
{
    float fVar1;
    float* in_EAX; // pointer to 4-float input vector (x, y, z, w)
    int thisPtr; // unaff_ESI
    uint index = stickIndex;
    float fVar3, fVar4, fVar5, fVar6, fVar7;
    float fVar10;
    double dVar8, dVar9;
    float local_38;

    // Load input vector components
    fVar4 = in_EAX[0]; // x
    fVar5 = in_EAX[1]; // y
    fVar6 = in_EAX[2]; // z
    fVar7 = in_EAX[3]; // w

    // === Horizontal magnitude (x,y) ===
    fVar3 = sqrtf(fVar5 * fVar5 + fVar4 * fVar4);
    // Store raw horizontal magnitude (clamped)
    *(float*)(thisPtr + 0x16b8 + index * 8) = clamp(fVar3, 0.0f, MAX_STICK_MAGNITUDE);

    // Compute horizontal angle-related diff: (DEADZONE_CENTER - x)
    dVar8 = (double)(DEADZONE_CENTER - fVar4);
    FLOAT_FUNC_00b9a9fa(); // likely sin/cos/atan function, consumes st(0), pushes result
    *(float*)(thisPtr + 0x1738 + index * 8) = (float)dVar8;

    // === Vertical magnitude (z,w) ===
    fVar3 = sqrtf(fVar7 * fVar7 + fVar6 * fVar6);
    // Store raw vertical magnitude (clamped)
    *(float*)(thisPtr + 0x16bc + index * 8) = clamp(fVar3, 0.0f, MAX_STICK_MAGNITUDE);

    // Compute vertical angle-related diff: (DEADZONE_CENTER - z)
    dVar8 = (double)(DEADZONE_CENTER - fVar6);
    FLOAT_FUNC_00b9a9fa();
    *(float*)(thisPtr + 0x173c + index * 8) = (float)dVar8;

    // === Processed horizontal component ===
    fVar1 = *(float*)(thisPtr + 0x16b0); // blend factor (sensitivity or deadzone)
    local_38 = sqrtf(fVar4 * fVar4 + fVar5 * fVar5); // recompute horizontal magnitude
    local_38 = clamp(local_38, 0.0f, MAX_STICK_MAGNITUDE);

    // Apply math functions to y component and magnitude
    dVar8 = (double)fVar5;
    FLOAT_FUNC_00b9a9fa(); // possibly sin(y)
    dVar9 = (double)local_38;
    FLOAT_FUNC_00b9af10(); // possibly cos(magnitude)
    // Blend between transformed value and raw magnitude
    fVar4 = (float)dVar9 * (MAX_STICK_MAGNITUDE - fVar1) + local_38 * fVar1;

    dVar9 = (double)(float)dVar8;
    FLOAT_FUNC_00b99e20(); // likely cos(y)
    fVar5 = (float)dVar9 * fVar4;

    dVar8 = (double)(float)dVar8;
    FLOAT_FUNC_00b99fcb(); // likely sin(y)
    fVar4 = (float)dVar8 * fVar4;

    // Store processed horizontal magnitude
    *(float*)(thisPtr + 0x17b8 + index * 8) = sqrtf(fVar4 * fVar4 + fVar5 * fVar5);
    // Store processed horizontal angle diff
    dVar8 = (double)(DEADZONE_CENTER - fVar5);
    FLOAT_FUNC_00b9a9fa();
    *(float*)(thisPtr + 0x1838 + index * 8) = (float)dVar8;

    // === Processed vertical component ===
    fVar6 = sqrtf(fVar6 * fVar6 + fVar7 * fVar7); // recompute vertical magnitude
    fVar6 = clamp(fVar6, 0.0f, MAX_STICK_MAGNITUDE);

    dVar8 = (double)fVar7;
    FLOAT_FUNC_00b9a9fa(); // sin(w)
    dVar9 = (double)fVar6;
    FLOAT_FUNC_00b9af10(); // cos(magnitude)
    fVar7 = (float)dVar9 * (MAX_STICK_MAGNITUDE - fVar1) + fVar6 * fVar1;

    dVar9 = (double)(float)dVar8;
    FLOAT_FUNC_00b99e20(); // cos(w)
    fVar6 = (float)dVar9 * fVar7;

    dVar8 = (double)(float)dVar8;
    FLOAT_FUNC_00b99fcb(); // sin(w)
    fVar7 = (float)dVar8 * fVar7;

    // Store processed vertical magnitude
    *(float*)(thisPtr + 0x17bc + index * 8) = sqrtf(fVar7 * fVar7 + fVar6 * fVar6);
    // Store processed vertical angle diff
    dVar8 = (double)(DEADZONE_CENTER - fVar6);
    FLOAT_FUNC_00b9a9fa();
    *(float*)(thisPtr + 0x183c + index * 8) = (float)dVar8;

    return;
}