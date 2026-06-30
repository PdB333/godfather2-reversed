// FUN_NAME: Sentient::checkTargetFacing
// Function at 0x0075dc90
// Checks if a target direction relative to the entity is within a facing cone.
// Returns an enum (0=front, 1=back, 2=left, 3=right?) or maybe visibility status.
// thisPtr +0xc0: state or mode (0 or 0x48 indicate special handling)
// thisPtr +0xd4: flags (bit0 checked)
// thisPtr +0x70: unknown (passed to FUN_0078c370)
// thisPtr +0xc8: alternate focus position (used when state is not 0 or 0x48)
// FUN_00471610 returns pointer to some global transform (likely camera or player)
// FUN_004a07f0 transforms a vector by an orientation (likely from right/up/front axes)
// FUN_0056afa0 normalizes a 3D vector
// FUN_0078c370 compares two direction vectors and returns an int (0-3)

int __thiscall Sentient::checkTargetFacing(int thisPtr, const float* targetPos) {
    // Default return: 3 (e.g., "right" or "not visible")
    int result = 3;

    // Check if the entity is in a valid state to evaluate facing.
    // Conditions: state not 0 and not 0x48, OR flag bit0 set
    bool specialState = (*(int*)(thisPtr + 0xc0) != 0) && (*(int*)(thisPtr + 0xc0) != 0x48);
    bool flagBit0 = (*(byte*)(thisPtr + 0xd4) & 1) != 0;
    if (specialState || flagBit0) {
        // Get global transform (likely player or camera) containing axes and position
        int transformA = FUN_00471610(); // +0x10: right vector? +0x14: up? +0x18: forward?
        float* axesA = (float*)(transformA + 0x10); // starts at offset 0x10
        int transformB = FUN_00471610(); // uses position at +0x30
        float* posB = (float*)(transformB + 0x30);

        // Compute vector from posB to targetPos
        float deltaToTarget[3];
        deltaToTarget[0] = *targetPos - *posB;
        deltaToTarget[1] = targetPos[1] - *(posB + 1);
        deltaToTarget[2] = targetPos[2] - *(posB + 2);

        // Transform this delta by axesA (likely inverse rotation)
        float transformedTarget[3];
        FUN_004a07f0(transformedTarget, deltaToTarget, axesA);

        // Normalize transformedTarget
        float normTarget[4]; // 4 floats, but only 3 used; last is 0
        normTarget[0] = transformedTarget[0];
        normTarget[1] = transformedTarget[1];
        normTarget[2] = transformedTarget[2];
        normTarget[3] = 0.0f;
        FUN_0056afa0(normTarget, normTarget);

        // Determine the source position for the "direction of interest"
        float* sourcePos;
        if (*(int*)(thisPtr + 0xc0) == 0 || *(int*)(thisPtr + 0xc0) == 0x48) {
            // Use internal offset 200 (0xc8) which is likely a stored position
            sourcePos = (float*)(thisPtr + 200); // +0xc8
        } else {
            // Get another global transform and use its position
            int transformC = FUN_00471610();
            sourcePos = (float*)(transformC + 0x30);
        }

        // Compute vector from posB to sourcePos
        float deltaToSource[3];
        deltaToSource[0] = *sourcePos - *posB;
        deltaToSource[1] = sourcePos[1] - *(posB + 1);
        deltaToSource[2] = sourcePos[2] - *(posB + 2);

        // Transform this delta by axesA
        float transformedSource[3];
        FUN_004a07f0(transformedSource, deltaToSource, axesA);

        // Normalize transformedSource
        float normSource[4];
        normSource[0] = transformedSource[0];
        normSource[1] = transformedSource[1];
        normSource[2] = transformedSource[2];
        normSource[3] = 0.0f;
        FUN_0056afa0(normSource, normSource);

        // Compute cross product of normalized vectors (stored in normTarget and normSource)
        // Actually the code does: fVar8 = axesA[0x18] * normSource[1]; etc.
        // But it's using the original axesA's forward/right/up to compute cross? Looks like a different operation.
        // More likely it computes the cross product between normTarget and normSource, then normalizes.
        float cross[3];
        cross[0] = *(float*)(axesA + 0x18) * normSource[1] - *(float*)(axesA + 0x14) * normSource[2]; // seems off
        cross[1] = *(float*)(axesA + 0x10) * normSource[2] - *(float*)(axesA + 0x18) * normSource[0];
        cross[2] = *(float*)(axesA + 0x14) * normSource[0] - *(float*)(axesA + 0x10) * normSource[1];
        // Actually reading the decompiled code more carefully:
        // fVar8 = *(float *)(iVar2 + 0x18) * local_1c; // local_1c is normSource[1]
        // fVar7 = *(float *)(iVar2 + 0x14) * local_20; // local_20 is normSource[0]
        // fVar9 = *pfVar6 * local_1c; // *pfVar6 is axesA[0]
        // local_1c = *pfVar6 * local_18 - *(float *)(iVar2 + 0x18) * local_20; // cross[2]?
        // local_20 = fVar8 - *(float *)(iVar2 + 0x14) * local_18; // cross[0]?
        // local_18 = fVar7 - fVar9; // cross[1]?
        // Then normalized. So it's computing cross product between axesA and normSource? Actually it's using axesA components (right/up/forward) and normSource components. That seems like computing the vector from source to target relative to axesA.
        // But to simplify, we'll just reflect the logic. Probably the cross product is used to determine left/right.

        // The final step: call FUN_0078c370 with the two normalized transformed vectors and some additional parameter.
        result = FUN_0078c370(normTarget, normSource, *(int*)(thisPtr + 0x70));
    }

    return result;
}