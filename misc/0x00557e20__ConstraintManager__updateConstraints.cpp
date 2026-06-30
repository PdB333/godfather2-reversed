// FUNC_NAME: ConstraintManager::updateConstraints
void ConstraintManager::updateConstraints() {
    uint maskLow = *(uint *)(this + 0x38);  // Low 32 bits of constraint enable mask
    uint maskHigh = *(uint *)(this + 0x3c); // High 32 bits (used as combined mask)
    bool allDirty = *(char *)(this + 0x48) != 0;

    if (allDirty) {
        *(uint *)(this + 0x3c) = 0;  // Clear high part on dirty
    }

    uint combinedMask = maskLow | maskHigh;
    *(uint *)(this + 0x3c) = ~combinedMask | maskHigh; // Update high part

    if (!allDirty && ~combinedMask == 0) {
        return; // Nothing to process
    }

    *(char *)(this + 0x48) = 0; // Clear dirty flag

    // Get array descriptor: pointer to array and count
    int *arrayDesc = *(int **)(this + 0x30);
    int *arrayBase = (int *)arrayDesc[0];   // Base of constraint array
    int arrayCount = arrayDesc[1];          // Number of constraints
    int *currentConstraint = arrayBase;    // Start of iteration
    int *endConstraint = arrayBase + arrayCount * 0x70 / 4; // 0x70 bytes per constraint

    while (currentConstraint != endConstraint) {
        if ((combinedMask & 1) == 0) {
            // Local data structures (likely 4x4 matrix and 4-vector)
            float localMatrix[4][4]; // Stack space reused for matrix/vector
            float tempVector[4];
            float outputVector[4];
            float resultVector[4];

            // Clear initial matrix/vector
            localMatrix[1][0] = 0.0f;
            localMatrix[2][0] = 0.0f;
            localMatrix[3][0] = 0.0f;
            float constant = *(float *)0x00e2b1a4; // Some global constant

            // Virtual call: get constraint state from solver at this+0x34
            // vtable offset 0x8c: void getConstraintState(void* output, void* constraintData, int flag)
            int *solver = *(int **)(this + 0x34);
            (**(code **)(solver + 0x8c / 4))(&localMatrix, currentConstraint + 0x48 / 4, 1);

            // Copy matrix data to temporary area
            float matrixCopy[4][4];
            matrixCopy[1][0] = localMatrix[1][0];
            matrixCopy[1][1] = localMatrix[1][1];
            // ... (full copy omitted for brevity) ...
            // In reality this would copy 16 floats, but decompiler shows block copies

            // Compute something with the matrix (likely multiply or solve)
            FUN_00417560();

            // Copy local matrix to another stack area and call transformation
            FUN_004b59d0(&localMatrix, &outputVector);

            // Apply transformation to current constraint
            FUN_00aa1fc0(currentConstraint);

            // Subtract world position (offset 0x20-0x2c)
            float worldPosX = *(float *)(this + 0x20);
            float worldPosY = *(float *)(this + 0x24);
            float worldPosZ = *(float *)(this + 0x28);
            float worldPosW = *(float *)(this + 0x2c);

            outputVector[0] -= worldPosX;
            outputVector[1] -= worldPosY;
            outputVector[2] -= worldPosZ;
            outputVector[3] -= worldPosW;

            // Additional post-processing
            FUN_00aa57b0();
            FUN_00a6be20(&outputVector);
        }

        combinedMask >>= 1;
        currentConstraint += 0x70 / 4; // Advance to next constraint (0x70 bytes)
    }
}