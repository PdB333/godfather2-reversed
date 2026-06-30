// FUNC_NAME: CameraManager::createCameraView
int* CameraManager::createCameraView(void)
{
    int iVar1;
    int iVar6;
    float fVar7;
    float fVar8;
    double dVar9;
    int local_84;
    int local_80;
    int local_7c;
    int local_78;
    int local_74;
    // Stack-based temporary structure for camera parameters
    struct CameraParams {
        Vector3 zeroVec;       // +0x00
        float clampFactor;    // +0x0C
        int param5;           // +0x10
        int targetObj;        // +0x14
        int paramNeg1;        // +0x18
        // There may be more, but we only name what's used
    } params;

    // Get current camera target (player or view target)
    local_84 = CameraManager::getCurrentTarget();  // FUN_005c7540
    if (*(int*)(g_cameraManager + 0x154) == 0) {
        iVar6 = *(int*)(**(int**)(__readfsdword(0x2c) + 0x24));
    } else {
        iVar6 = *(int*)(g_cameraManager + 0x14);
    }

    // Save transform matrix from target object (16 floats at +0x40..+0x7C)
    Vector4 row0 = *(Vector4*)(iVar6 + 0x40);
    Vector4 row1 = *(Vector4*)(iVar6 + 0x50);
    Vector4 row2 = *(Vector4*)(iVar6 + 0x60);
    Vector4 row3 = *(Vector4*)(iVar6 + 0x70);
    float deltaTime = *(float*)(iVar6 + 0x14C);  // from target's time delta

    // Global update (likely frame advance)
    FUN_00b9c041();

    // Compute interpolation factor
    fVar7 = g_smoothFactor / deltaTime;  // g_smoothFactor = DAT_00e446f4
    fVar8 = g_clampMin;  // DAT_00e2b1a4
    if (fVar8 < fVar7 && fVar7 < g_clampMax) {  // g_clampMax = DAT_00e448cc
        fVar8 = fVar7;
    } else if (fVar7 <= g_clampMin) {
        fVar8 = g_clampMin;
    } else {
        fVar8 = g_clampMax;
    }

    // Interpolate translation with damping
    row3.x = fVar8 * row2.x + row3.x;
    row3.y = fVar8 * row2.y + row3.y;
    row3.z = fVar8 * row2.z + row3.z;

    // Build temporary camera parameters
    params.zeroVec = Vector3(0,0,0);
    params.clampFactor = g_clampMin;
    params.param5 = 5;
    params.targetObj = iVar6;
    params.paramNeg1 = -1;

    // Allocate handle structure (2 ints)
    int* handle = (int*)FUN_009c8e50(8);
    int* stackPtr = nullptr;
    if (handle != nullptr) {
        handle[0] = 0;
        handle[1] = 0;
        stackPtr = (int*)(g_allocStack + 0x14);  // DAT_01206880 + 0x14
        **(undefined4**)(g_allocStack + 0x14) = &s_HandleVTable;  // PTR_LAB_0112624c
        *stackPtr = *stackPtr + 4;
        *(int**)*stackPtr = handle;
        *stackPtr = *stackPtr + 4;
        stackPtr = handle;
    }

    // Process camera params (likely raycast or setup)
    int result = FUN_004eacb0(local_84);  // passes current target
    if (((local_80 == 0 && local_7c == 0) && (local_78 == 0 && local_74 == 0)) ||
        (int* tmp = (int*)FUN_004e0f60(); tmp == nullptr) ||
        (*tmp == 0)) {
        local_84 = 0;
    } else {
        FUN_004df210(*tmp, &params.zeroVec, uVar2, 4);
    }

    // Update handle reference
    if (*stackPtr != 0) {
        *(undefined4*)(*stackPtr + 8) = 0;
        *stackPtr = 0;
    }
    *stackPtr = local_84;
    if (local_84 != 0) {
        *(int**)(local_84 + 8) = stackPtr;
    }

    // Allocate and attach a secondary object (listener?)
    int* secondaryObj = (int*)FUN_009c8f80();
    local_80 = 2;
    local_7c = 0x10;
    local_78 = 0;
    undefined4* obj = (undefined4*)(**(code**)*secondaryObj)(0xC, &local_80);
    if (obj == nullptr) {
        obj = nullptr;
    } else {
        obj[1] = 0;
        *obj = &s_SecondaryVTable;  // PTR_LAB_00e372c4
        obj[2] = g_nextId++;
    }
    stackPtr[1] = (int)obj;
    obj[1] = obj[1] + 1;  // ref count increment?

    // Manage reference to target (local_84)
    iVar6 = *stackPtr;
    iVar1 = stackPtr[1];
    if (iVar6 != 0) {
        if (*(int*)(iVar6 + 0x20) != 0) {
            int* refCount = (int*)(*(int*)(iVar6 + 0x20) + 4);
            *refCount = *refCount - 1;
            if (*(int**)(iVar6 + 0x20))[1] == 0) {
                (**(code**)(**(int**)(iVar6 + 0x20) + 4))();
            }
            *(undefined4*)(iVar6 + 0x20) = 0;
        }
        *(int*)(iVar6 + 0x20) = iVar1;
        if (iVar1 != 0) {
            *(int*)(iVar1 + 4) = *(int*)(iVar1 + 4) + 1;
            return stackPtr;
        }
    }
    return stackPtr;
}