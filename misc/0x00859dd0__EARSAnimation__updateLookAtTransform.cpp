// FUNC_NAME: EARSAnimation::updateLookAtTransform
void __thiscall EARSAnimation::updateLookAtTransform(EARSAnimation *this, void *targetInfo) {
    // +0x3c: targetInfo field for animation state index
    int stateIndex = *(int *)((char *)targetInfo + 0x3c);
    // Table containing bit offset for each state
    byte bitOffset = *(byte *)(DAT_00e5407c + stateIndex * 2) * 4;
    uint oldState = (*(uint *)((char *)this + 0xd0) >> (bitOffset & 0x1f)) & 0xf;
    uint newState = oldState + 4;
    if (newState > 0xf) newState = 0xf;
    // Update bitfield
    uint mask = ~(0xf << (bitOffset & 0x1f));
    *(uint *)((char *)this + 0xd0) = (*(uint *)((char *)this + 0xd0) & mask) | (newState << (bitOffset & 0x1f));
    // Check transition from low to high state and existence of blend matrices
    if (oldState < 0xc && newState > 0xb) {
        // +0x1a8: pointer to current blend matrix (or null)
        // +0x1ac, +0x1b0, +0x1b4: additional transform data (or null)
        int *blendMatrix = (int *)((char *)this + 0x1a8);
        if (*blendMatrix != 0 || *(int *)((char *)this + 0x1ac) != 0 ||
            *(int *)((char *)this + 0x1b0) != 0 || *(int *)((char *)this + 0x1b4) != 0) {
            EARSAnimation *savedThis = this;
            // Retrieve identity matrix (4x4)
            float *identityMatrix = FUN_00471610();
            // Copy identity into local matrix
            float localMatrix[4][4];
            for (int i = 0; i < 16; i++) {
                ((float *)localMatrix)[i] = identityMatrix[i];
            }
            // Compute direction vector: targetPosition - sourcePosition
            // targetInfo offsets: +0x20 (x), +0x24 (y), +0x28 (z)
            // sourceInfo offsets: +0x14 (x), +0x18 (y), +0x1c (z)
            float dirX = *(float *)((char *)targetInfo + 0x20) - *(float *)((char *)targetInfo + 0x14);
            float dirY = *(float *)((char *)targetInfo + 0x24) - *(float *)((char *)targetInfo + 0x18);
            float dirZ = *(float *)((char *)targetInfo + 0x28) - *(float *)((char *)targetInfo + 0x1c);
            // Normalize direction
            float normDir[3] = { dirX, dirY, dirZ };
            FUN_0043a210(normDir, normDir); // in-place normalization
            // Use identity matrix rows to compute cross product (likely constructing orthonormal basis)
            // Local matrix rows: localMatrix[0][0..3] = first row etc.
            // We'll reconstruct: localMatrix[1][0..2] = identity row2? Actually from decomp: local_78, local_7c, local_80 are from matrix.
            float upX = localMatrix[1][0]; // assuming row-major: cross with row1 (up?)
            float upY = localMatrix[1][1];
            float upZ = localMatrix[1][2];
            // Cross product: up x dir
            float rightX = upY * normDir[2] - upZ * normDir[1];
            float rightY = upZ * normDir[0] - upX * normDir[2];
            float rightZ = upX * normDir[1] - upY * normDir[0];
            // Normalize right
            float normRight[3] = { rightX, rightY, rightZ };
            FUN_0043a210(normRight, normRight);
            // Set the three basis vectors into matrix
            // localMatrix[0][0..2] = normalized direction (forward)
            // localMatrix[1][0..2] = normalized right (or up)
            localMatrix[0][0] = normDir[0];
            localMatrix[0][1] = normDir[1];
            localMatrix[0][2] = normDir[2];
            localMatrix[1][0] = normRight[0];
            localMatrix[1][1] = normRight[1];
            localMatrix[1][2] = normRight[2];
            // Recompute up as cross of forward and right
            float newUpX = normDir[1] * normRight[2] - normDir[2] * normRight[1];
            float newUpY = normDir[2] * normRight[0] - normDir[0] * normRight[2];
            float newUpZ = normDir[0] * normRight[1] - normDir[1] * normRight[0];
            localMatrix[2][0] = newUpX;
            localMatrix[2][1] = newUpY;
            localMatrix[2][2] = newUpZ;
            // Convert matrix to Euler angles or quaternion (likely)
            float convertedData[??];
            FUN_0044b4e0(convertedData, localMatrix);
            // Get something from vtable (e.g., animation ID)
            // +0xf8: vtable pointer offset
            int vtablePtr = **(int **)((char *)savedThis + 0xf8);
            int someId = ((int (*)(int, int, int, int))(*(int *)(vtablePtr + 0x58)))(0, 0, 0xffffffff, 0);
            // Apply the conversion to the blend matrix
            FUN_004df330(&savedThis, blendMatrix, convertedData, someId);
            if (savedThis != 0) {
                *(int *)((char *)savedThis + 8) = 0; // clear some flag
            }
        }
    }
}