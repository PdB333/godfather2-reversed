// FUNC_NAME: DecalManager::fillDecalTransform
// Address: 0x008fd0f0
// This function fills a decal transform structure from an impact entity or camera.

struct DecalTransform {
    // +0x00: first row of transform? (Actually used as flags/IDs)
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    // +0x10: First 4x4 matrix (row-major), diagonal initially set to 1.0
    float matrix1[16];
    // +0x50: Second 4x4 matrix
    float matrix2[16];
};

// Global constant (likely 1.0f)
extern const float g_onePointZero; // _DAT_00d5780c

// Global pointer to some manager
extern uintptr_t* g_sceneManagerPtr; // DAT_012233a0

// Forward declarations of callees
int __thiscall isValidTransform(int param_ec); // FUN_008fc140
int* __thiscall getGlobalCamera(); // FUN_00471610
int __thiscall getCameraTransform(int cameraObj); // FUN_008f18e0
void __thiscall copyMatrixFrom(int* dest, int src); // FUN_008fcbf0
void __thiscall setDefaultMatrix(int* dest); // FUN_008fcc40

void __thiscall DecalManager::fillDecalTransform(int thisPtr, int param2, DecalTransform* outTransform) {
    int* entityArray;
    int entityCount;
    int* pEntityData;
    uint index;
    int selectedEntity;

    // Initialize output structure
    outTransform->field_0 = 0;
    outTransform->field_4 = 0;
    outTransform->field_8 = 0;
    outTransform->field_C = 0;

    // Set matrix1 to identity (diagonal elements set to 1.0)
    outTransform->matrix1[0] = g_onePointZero;
    outTransform->matrix1[5] = g_onePointZero;
    outTransform->matrix1[10] = g_onePointZero;
    outTransform->matrix1[15] = g_onePointZero;
    outTransform->matrix1[1] = 0.0f;
    outTransform->matrix1[2] = 0.0f;
    outTransform->matrix1[3] = 0.0f;
    outTransform->matrix1[4] = 0.0f;
    outTransform->matrix1[6] = 0.0f;
    outTransform->matrix1[7] = 0.0f;
    outTransform->matrix1[8] = 0.0f;
    outTransform->matrix1[9] = 0.0f;
    outTransform->matrix1[11] = 0.0f;
    outTransform->matrix1[12] = 0.0f;
    outTransform->matrix1[13] = 0.0f;
    outTransform->matrix1[14] = 0.0f;

    // Also zero out the second matrix
    for (int i = 0; i < 16; i++) {
        outTransform->matrix2[i] = 0.0f;
    }

    // Try to get transform from an impact entity
    if (*(int*)(thisPtr + 0x1c) != 0) {
        int impactEntity = *(int*)(thisPtr + 0x1c);
        int* pTargetValue = (int*)(impactEntity + 0xc4);
        if (*pTargetValue != 0) {
            index = 0;
            if (*(uint*)(thisPtr + 0x24) != 0) {
                entityArray = *(int**)(thisPtr + 0x20);
                do {
                    selectedEntity = *entityArray;
                    if (*(int*)(selectedEntity + 0x74) == *pTargetValue) {
                        goto found;
                    }
                    index++;
                    entityArray++;
                } while (index < *(uint*)(thisPtr + 0x24));
            }
            selectedEntity = 0;
        }
found:
        outTransform->field_0 = *(int*)(selectedEntity + 0x74);
        int transformCheck = isValidTransform(selectedEntity + 0xec);
        if (transformCheck != 0) {
            return;
        }
    }

    // Fallback: use camera transform if available
    uintptr_t* sceneMgr = (uintptr_t*)(*(int*)(g_sceneManagerPtr + 4));
    if ((sceneMgr != nullptr) && (sceneMgr != (uintptr_t*)0x1f30)) {
        outTransform->field_4 = 1;
        int camera = getGlobalCamera();
        int cameraObj = getCameraTransform(camera + 0x30);
        if (cameraObj != 0) {
            // Copy camera world matrix into matrix1 (offset 0x10)
            float* src = (float*)(cameraObj + 0x60);
            for (int i = 0; i < 16; i++) {
                outTransform->matrix1[i] = src[i];
            }
            // Copy additional data into matrix2 (offset 0x50)
            copyMatrixFrom((int*)(&outTransform->matrix2), cameraObj + 0xb0);
            return;
        }
        // Alternative: get another matrix from camera
        camera = getGlobalCamera();
        // Overwrite matrix1 with camera data at offset 0x30?
        float* src2 = (float*)(camera + 0x30);
        for (int i = 0; i < 16; i++) {
            outTransform->matrix1[i] = src2[i];
        }
        setDefaultMatrix((int*)(&outTransform->matrix2));
    }
    return;
}