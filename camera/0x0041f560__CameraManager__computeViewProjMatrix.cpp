// FUNC_NAME: CameraManager::computeViewProjMatrix
struct CameraMatrix {
    float m[4][4]; // +0x00, row-major 4x4 matrix
    // ... other fields up to size 0x210
};

extern CameraMatrix g_cameraMatrices[?];       // DAT_01163790
extern char g_cameraFlags[?];                  // DAT_01163840
extern float g_leftProjRow[4];                 // DAT_00e2e7a0
extern float g_leftEyeTranslation[4];          // DAT_00e2e7b0
extern float g_rightProjRow[4];                // DAT_011280b0
extern float g_rightEyeTranslation[4];         // DAT_011280c0

bool __fastcall isStereoModeActive();           // FUN_004166b0
void __thiscall getViewMatrix(void *this, float outMatrix[4][4]); // FUN_00417560

float *__fastcall CameraManager::computeViewProjMatrix(void *this, int cameraIndex) {
    int offset = cameraIndex * 0x210;
    char stereoActive = isStereoModeActive();
    if (stereoActive != 0) {
        // Determine which stereo eye this matrix belongs to based on a flag
        char eyeFlag = g_cameraFlags[(int)this];  // extraout_EDX derived from this
        if ((((byte)((eyeFlag != 0) * 2 + 1)) < 2)) {
            // Use left eye projection/offset
            float *projRow = g_leftProjRow;
            float *eyeTrans = g_leftEyeTranslation;
        } else {
            // Use right eye projection/offset
            float *projRow = g_rightProjRow;
            float *eyeTrans = g_rightEyeTranslation;
        }

        // Get the view matrix (4x4) from the camera system
        float viewMatrix[4][4];
        getViewMatrix(this, viewMatrix);

        // Build the combined view-projection matrix
        float *dest = (float *)&g_cameraMatrices[cameraIndex];
        float *projRow = ...; // use from above
        float *eyeTrans = ...;
        float fVar1 = projRow[0];
        float fVar2 = projRow[1];
        float fVar3 = projRow[2];
        float fVar4 = projRow[3];

        // Column-wise scaling of view matrix rows by projection row elements
        dest[0*4 + 0] = fVar1 * viewMatrix[0][0];
        dest[0*4 + 1] = fVar2 * viewMatrix[0][1];
        dest[0*4 + 2] = fVar3 * viewMatrix[0][2];
        dest[0*4 + 3] = fVar4 * viewMatrix[0][3];

        dest[1*4 + 0] = fVar1 * viewMatrix[1][0];
        dest[1*4 + 1] = fVar2 * viewMatrix[1][1];
        dest[1*4 + 2] = fVar3 * viewMatrix[1][2];
        dest[1*4 + 3] = fVar4 * viewMatrix[1][3];

        dest[2*4 + 0] = fVar1 * viewMatrix[2][0];
        dest[2*4 + 1] = fVar2 * viewMatrix[2][1];
        dest[2*4 + 2] = fVar3 * viewMatrix[2][2];
        dest[2*4 + 3] = fVar4 * viewMatrix[2][3];

        dest[3*4 + 0] = fVar1 * viewMatrix[3][0] + eyeTrans[0];
        dest[3*4 + 1] = fVar2 * viewMatrix[3][1] + eyeTrans[1];
        dest[3*4 + 2] = fVar3 * viewMatrix[3][2] + eyeTrans[2];
        dest[3*4 + 3] = fVar4 * viewMatrix[3][3] + eyeTrans[3];
    }

    return (float *)&g_cameraMatrices[cameraIndex];
}