// FUNC_NAME: EffectManager::submitEffectFromInfo

void __fastcall EffectManager::submitEffectFromInfo(int this, void* param_1)
{
    // this - EffectManager singleton (from DAT_011298a0 = g_effectManager)
    // param_1 - pointer to effect info structure (EffectorInfo?)
    //   +0x08: positionX (float)
    //   +0x0C: positionY (float)
    //   +0x10: positionZ or rotation (float)
    //   +0x14: flag (int) - if zero, rotation is omitted

    int ready;
    int cameraManager;
    float vec4Zero; // g_zeroVector @ 0x00d5780c (usually {0,0,0,0})

    // Local stack object representing the effect to submit
    float effectData[16]; // 4 vectors of 4 floats, aligned to 16 bytes
    int* effectVTablePtr; // points to g_effectVTable @ 0x00d8bff4
    undefined4* effectDataPtr; // points to effectData[0]

    // Local variables for part of effectData later overwritten
    int flag;               // from param_1+0x14
    float rotationW;        // from global at offset 0x84
    float rotX, rotY, rotZ; // from cameraManager

    // Check if effect system is ready (e.g., rendering active)
    ready = isEffectSystemReady(); // FUN_0079f9d0
    if (ready == 0) {
        return;
    }

    // Fetch the camera/transform manager (e.g., getActiveCamera)
    cameraManager = getCameraManager(); // FUN_009be470

    // Initialize first three vectors of effectData to zero (using g_zeroVector)
    vec4Zero = g_zeroVector; // _DAT_00d5780c
    effectData[0] = vec4Zero; effectData[1] = 0; effectData[2] = 0; effectData[3] = 0; // first vector
    effectData[4] = 0; effectData[5] = vec4Zero; effectData[6] = 0; effectData[7] = 0; // second
    effectData[8] = 0; effectData[9] = 0; effectData[10] = vec4Zero; effectData[11] = 0; // third
    effectData[12] = 0; effectData[13] = 0; effectData[14] = 0; effectData[15] = vec4Zero; // fourth

    // Transform the fourth vector from camera's world matrix?
    transformVector(*(float*)(cameraManager + 0x70), 0, 0, effectData); // FUN_0056b8a0
    // effectData now contains a transformed basis or direction

    // Overwrite parts of effectData with additional data
    effectData[15] = vec4Zero; // reset fourth vector's w component?
    flag = *(int*)(param_1 + 0x14);
    rotationW = *(float*)(g_effectManager + 0x84); // some global rotation offset?
    if (flag == 0) {
        effectData[0] = 0; // first vector x set to 0
    } else {
        effectData[0] = *(float*)(param_1 + 0x10); // first vector x from param_1
    }
    effectData[4] = *(float*)(param_1 + 0x08); // second vector x from positionX
    effectData[5] = *(float*)(param_1 + 0x0C); // second vector y from positionY

    // Fetch additional rotation from cameraManager (e.g., camera quaternion)
    rotX = *(float*)(cameraManager + 0x68);
    rotY = *(float*)(cameraManager + 0x6C);
    rotZ = *(float*)(cameraManager + 0x64); // z? order: +0x64, +0x68, +0x6C
    effectData[12] = rotZ; // overwrite fourth vector components
    effectData[13] = rotX;
    effectData[14] = rotY;

    // Set up the effect object (vtable + data pointer)
    effectVTablePtr = &g_effectVTable; // PTR_LAB_00d8bff4
    effectDataPtr = effectData;
    *(int*)(effectDataPtr - 2) = (int)effectVTablePtr; // local_70 = &PTR; local_6c = &data; local_5c = 1
    // Note: The exact stack layout is tricky, but we assume the vtable pointer and data pointer are placed before effectData.
    // The call to FUN_004a4bd0 takes the address of the vtable pointer (i.e., the object's base address).

    submitEffectToRenderer(&effectVTablePtr); // FUN_004a4bd0
}