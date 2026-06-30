// FUNC_NAME: CameraSystem::getOrientationVectors
void __thiscall CameraSystem::getOrientationVectors(int this, float *outForward, float *outRight) {
    int engineMgr = *(int *)(DAT_01223480 + 0x24); // Game engine singleton, offset +0x24
    float matrix[5]; // 20-byte transformation matrix
    float temp[4];   // 4-byte work buffer (quaternion or rotation)

    // Initialize engine subsystem
    FUN_0045cbe0();

    // Set first element of matrix to constant (likely 1.0f)
    matrix[0] = *(float *)&DAT_00e2b1a4;
    // Remaining matrix elements implicitly zeroed through local_14..local_20 = 0

    // Get camera component from this+0x2E8
    int cameraComp = *(int *)(this + 0x2E8);          // +0x2E8: CameraComponent*
    int cameraVtable = *(int *)(cameraComp + 0x10);   // +0x10: vtable pointer
    void (*computeTransform)(float *, int, float *) = 
        (void (*)(float *, int, float *))*(int *)(cameraVtable + 0x1C); // vtable+0x1C: transform function

    // Call transform with matrix, a parameter from engine+0x6C+4, and temp buffer
    computeTransform(matrix, *(int *)(*(int *)(engineMgr + 0x6C) + 4), temp);

    // The called function stores results into stack/registers; copy to output vectors
    // These fields correspond to unaff_ESI, uStack_78, uStack_74, uStack_6c, uStack_68, uStack_64
    outForward[0] = *(float *)&unaff_ESI; // Forward X
    outForward[1] = *(float *)&uStack_78; // Forward Y
    outForward[2] = *(float *)&uStack_74; // Forward Z
    outRight[0] = *(float *)&uStack_6c;   // Right X
    outRight[1] = *(float *)&uStack_68;   // Right Y
    outRight[2] = *(float *)&uStack_64;   // Right Z
}