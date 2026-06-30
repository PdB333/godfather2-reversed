// FUNC_NAME: Frustum::createFromParams
// This function constructs a frustum (likely for 2D or 3D clipping) using parameters provided.
// addr: 0x005330e0
// globals: g_screenWidth (DAT_00e44564), g_orthoNearPlane (DAT_00e2b1a4) - guessed based on usage.
// The allocation function FUN_0060cd00 returns a float array of appropriate size for frustum planes.
// The function then fills the array with plane equations (or vertex data) and registers it via FUN_0060cde0.
// param_6 (bool bIsOrtho) chooses between 4-plane (2D) and 6-plane (3D) frustum generation.

#include <cstdint>

extern float g_screenWidth;       // DAT_00e44564 - seems to be screen viewport width
extern float g_orthoNearPlane;    // DAT_00e2b1a4 - likely near plane constant for orthographic case
extern float* __fastcall allocFrustumBuffer(int poolId, int size, int align, int flag1, int flag2); // FUN_0060cd00
extern void registerFrustum(float* pFrustumData); // FUN_0060cde0

void createFrustum(float left, float top, float nearVal, float right, float farVal, bool bIsOrtho)
{
    float* pBuffer;

    if (!bIsOrtho) {
        // 2D/Orthographic frustum (4 planes, 16 floats)
        pBuffer = allocFrustumBuffer(0xd, 4, 0, 1, 0);
        if (pBuffer) {
            float fLeftMinus = g_screenWidth - left; // = rightExtent from screen width
            pBuffer[3] = nearVal;
            pBuffer[7] = nearVal;
            pBuffer[0] = fLeftMinus;
            pBuffer[1] = fLeftMinus;
            pBuffer[2] = top;
            pBuffer[4] = left;
            pBuffer[5] = fLeftMinus;
            pBuffer[6] = top + right; // note: right parameter used as height offset? Might be bottom value
            pBuffer[8] = left;
            pBuffer[9] = left;
            pBuffer[10] = top + right;
            pBuffer[11] = nearVal + farVal;
            pBuffer[12] = fLeftMinus;
            pBuffer[13] = left;
            pBuffer[14] = top;
            pBuffer[15] = nearVal + farVal;
            registerFrustum(pBuffer);
        }
    }
    else {
        // 3D/Perspective frustum (6 planes, 24 floats)
        pBuffer = allocFrustumBuffer(0xd, 4, 0, 1, 0);
        float fOrthoNear = g_orthoNearPlane;
        if (pBuffer) {
            float fLeftMinus = g_screenWidth - left;
            pBuffer[3] = nearVal;
            pBuffer[9] = nearVal;
            pBuffer[0] = fLeftMinus;
            pBuffer[1] = fLeftMinus;
            pBuffer[2] = top;
            pBuffer[4] = 0.0f;
            pBuffer[5] = 0.0f;
            pBuffer[6] = left;
            pBuffer[7] = fLeftMinus;
            pBuffer[8] = top + right;
            pBuffer[10] = fOrthoNear;
            pBuffer[11] = 0.0f;
            pBuffer[12] = left;
            pBuffer[13] = left;
            pBuffer[14] = top + right;
            pBuffer[15] = nearVal + farVal;
            pBuffer[16] = fOrthoNear;
            pBuffer[17] = fOrthoNear;
            pBuffer[18] = fLeftMinus;
            pBuffer[19] = left;
            pBuffer[20] = top;
            pBuffer[21] = nearVal + farVal;
            pBuffer[22] = 0.0f;
            pBuffer[23] = fOrthoNear;
            registerFrustum(pBuffer);
        }
    }
}