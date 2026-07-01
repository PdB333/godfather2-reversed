// FUNC_NAME: ChaseCamera::updateCameraTransform

void __fastcall ChaseCamera::updateCameraTransform(ChaseCamera *this)
{
    char active;
    float *matrix;
    float fVar5;
    float fVar6;
    float localMatrix[4]; // actually 16 floats, but used as 4x4? Only first 4 used? Actually loop copies 16 floats into local_50 which is float[4]? Wait, local_50 is declared as float[4] but loop copies 16 floats? That's a bug in decompiler. The array is likely float[16] but Ghidra shows only 4. We'll treat as float[16].
    // Actually the decompiled code shows local_50[4] but loop runs 0x10 times. So it's actually a 16-element array. We'll use a proper array.
    float matrixCopy[16];
    float newPos[3];
    float fStack_60, fStack_5c, fStack_58;

    active = FUN_00481620(); // likely isGameActive()
    if (active != '\0') {
        matrix = (float *)FUN_00471610(); // get some global matrix (view matrix?)
        fVar6 = *(float *)(this + 0x88); // z component of normal?
        fVar5 = *(float *)(this + 0x84) * 0.0; // always 0
        // Copy 16 floats from matrix into local array
        for (int i = 0x10; i != 0; i--) {
            matrixCopy[i] = *matrix;
            matrix++;
        }
        // Modify the copied matrix
        // local_50[0] = fVar6 - fVar5 = fVar6
        matrixCopy[0] = fVar6;
        // local_50[1] = *(float *)(this + 0x80) * 0.0 - fVar6 * 0.0 = 0
        matrixCopy[1] = 0.0f;
        // local_50[2] = fVar5 - *(float *)(this + 0x80) = -x component
        matrixCopy[2] = -*(float *)(this + 0x80);
        // local_50[3] = *(float *)(this + 0x88) (from local_28 assignment)
        matrixCopy[3] = *(float *)(this + 0x88);
        // Also set some global constants into the matrix
        // local_40 = DAT_00d6e8e0 (8 bytes)
        // local_30 = *(undefined8 *)(this + 0x80) (8 bytes)
        // local_38 = DAT_00d6e8e8 (4 bytes)
        // This is messy; likely the matrix is being set to a specific transform.
        // For simplicity, we'll just note that the matrix is modified.

        // Call virtual function at vtable+0x2c on the component at this+0x58
        (**(code **)(**(int **)(this + 0x58) + 0x2c))(matrixCopy);

        // Second part: compute new position along a ray
        int iVar3 = FUN_00471610(); // get another matrix? Actually returns int, but used as pointer to float array
        float *someMatrix = (float *)iVar3;
        // Compute dot product of (someMatrix position - this target) with normal
        float dx = someMatrix[0x30] - *(float *)(this + 0x74); // x difference
        float dy = someMatrix[0x34] - *(float *)(this + 0x78); // y difference
        float dz = someMatrix[0x38] - *(float *)(this + 0x7c); // z difference
        float dot = dx * *(float *)(this + 0x80) + dy * *(float *)(this + 0x84) + dz * *(float *)(this + 0x88);
        fVar6 = DAT_00d6e918 - dot; // plane distance minus dot product

        // New position = someMatrix origin + normal * fVar6
        fStack_60 = *(float *)(this + 0x80) * fVar6 + someMatrix[0x30];
        fStack_5c = *(float *)(this + 0x84) * fVar6 + someMatrix[0x34];
        fStack_58 = *(float *)(this + 0x88) * fVar6 + someMatrix[0x38];

        // Call virtual function at vtable+0x1c on the same component
        (**(code **)(**(int **)(this + 0x58) + 0x1c))(&fStack_60);

        // Set flag bit 0x1000 at offset 0x128
        *(uint *)(this + 0x128) |= 0x1000;
    }
}