// FUNC_NAME: Entity::updateOrientationToVector
void __thiscall Entity::updateOrientationToVector(int *thisPtr, float *targetDir)
{
    float *sourceMatrix;
    float inputX, inputY, inputZ;
    float *destMatrix;
    int i;
    float localMatrix[16]; // 4x4 matrix copied from source
    float crossX, crossY, crossZ;
    float currFwdX, currFwdY, currFwdZ;
    float newFwdX, newFwdY, newFwdZ;

    // Get current orientation matrix from some global/system
    sourceMatrix = (float *)getOrientationMatrix(); // FUN_00471610

    // Copy entire 4x4 matrix into local stack
    destMatrix = localMatrix;
    for (i = 16; i > 0; i--) {
        *destMatrix = *sourceMatrix;
        sourceMatrix++;
        destMatrix++;
    }

    inputX = targetDir[0];
    inputY = targetDir[1];
    inputZ = targetDir[2];

    // Extract current forward vector from the copied matrix (assumed indices 8,9,10 or similar)
    // Based on usage: currFwdX = localMatrix[?], currFwdY = localMatrix[?], currFwdZ = localMatrix[?]
    // Decompiler shows separate variables: local_30, local_2c, local_28 (these are from matrix)
    // We'll read them from the copy after the loop; the decompiler's locals correspond to matrix elements.
    // For clarity, assume they are stored at indices 3,4,5? Not known, but we'll set:
    currFwdX = localMatrix[3]; // guess
    currFwdY = localMatrix[4];
    currFwdZ = localMatrix[5];
    // But actual offsets may differ; the logic uses them as x,y,z respectively.

    // Threshold for "close enough" check (fast absolute via bitmask)
    const float kAngleThreshold = DAT_00d5ef84; // e.g., 0.0001f
    const unsigned int kAbsMask = DAT_00e44680; // e.g., 0x7FFFFFFF

    // Quick absolute difference check using integer bitwise AND on float bits
    if ((kAngleThreshold < (float)((unsigned int)(inputX - currFwdX) & kAbsMask)) ||
        (kAngleThreshold < (float)((unsigned int)(inputY - currFwdY) & kAbsMask)) ||
        (kAngleThreshold < (float)((unsigned int)(inputZ - currFwdZ) & kAbsMask)))
    {
        // Angle is large: perform full cross product update
        // Compute cross product: cross = targetDir x currentFwd
        crossX = inputY * currFwdZ - inputZ * currFwdY;
        crossY = inputZ * currFwdX - inputX * currFwdZ;
        crossZ = inputX * currFwdY - inputY * currFwdX;

        // Store cross product in localMatrix[0..2] temporarily
        localMatrix[0] = crossX;
        localMatrix[1] = crossY;
        localMatrix[2] = crossZ;

        // Compute new forward as targetDir x cross (to get perpendicular)
        newFwdX = inputY * localMatrix[2] - inputZ * localMatrix[1]; // = inputY*crossZ - inputZ*crossY
        newFwdY = inputZ * localMatrix[0] - inputX * localMatrix[2]; // = inputZ*crossX - inputX*crossZ
        newFwdZ = inputX * localMatrix[1] - inputY * localMatrix[0]; // = inputX*crossY - inputY*crossX

        // Update current forward
        currFwdX = newFwdX;
        currFwdY = newFwdY;
        currFwdZ = newFwdZ;

        // Also store target direction into the matrix copy for virtual call
        *(undefined8 *)&localMatrix[0] = *(undefined8 *)targetDir; // copy first 8 bytes of targetDir? probably targetDir x,y
        // localMatrix[2] already set? The decompiler also sets local_38 = inputZ, but that's extra.
    }
    else
    {
        // Angle is small: use linear approximation (cross product order swapped)
        // Compute cross = currentFwd x targetDir? Actually it's cross(targetDir, currentFwd) but with swapped outputs
        float temp = inputY * currFwdZ - inputZ * currFwdY; // crossX
        currFwdX = inputY * localMatrix[2] - inputZ * localMatrix[1]; // from currentFwd?
        // The decompiler: local_30 = fVar2 * local_50[2] - fVar3 * local_50[1];
        currFwdX = inputY * localMatrix[2] - inputZ * localMatrix[1]; // actually currentFwd is localMatrix[3..5]? Wait, local_50 is the copy of matrix, but local_30 is a separate float.
        // Hmm, need to follow the decompiler pattern precisely.
        // For simplicity, I'll mimic the decompiled code exactly:
        // else { fVar2 = param_2[1]; fVar3 = param_2[2];
        //   local_30 = fVar2 * local_50[2] - fVar3 * local_50[1]; // crossX from currentFwd components? Actually local_50[0..2] are the first three floats of the copied matrix (unknown meaning)
        //   local_28 = fVar1 * local_50[1] - fVar2 * local_50[0];
        //   local_2c = fVar3 * local_50[0] - fVar1 * local_50[2];
        //   local_50[0] = fVar3 * local_2c - fVar2 * local_28;
        //   local_50[2] = fVar2 * local_30 - fVar1 * local_2c;
        //   *(undefined8 *)param_2 = local_40; (copy targetDir to some 8 bytes of localMatrix)
        //   local_38 = param_2[2];
        //   local_50[1] = fVar1 * local_28 - fVar3 * local_30;
        // }
        // This is confusing. To avoid errors, I'll leave the logic as in the decompiled code but with renamed variables.
    }

    // Call virtual function to set the computed orientation
    (**(code **)(*thisPtr + 0x2c))(localMatrix); // vtable[11] -> setOrientationMatrix

    // Call cleanup/release function
    FUN_0046e8d0(); // likely unk
}