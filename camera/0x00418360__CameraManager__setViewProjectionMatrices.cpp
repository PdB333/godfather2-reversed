// FUNC_NAME: CameraManager::setViewProjectionMatrices
void __thiscall CameraManager::setViewProjectionMatrices(void* thisPtr, const float* viewMatrix, const float* projMatrix, char isPrimary)
{
    int* transformData;
    float* dst;

    // Store global static matrix references (likely identity or default)
    DAT_01205444 = DAT_011f3910;
    
    // Check if this object is the globally active camera and has a shadow map present (offset +0xa4)
    transformData = *(int**)((char*)thisPtr + 4);  // +0x4: m_pTransformData
    if (DAT_012058e8 == transformData && *(int*)((char*)transformData + 0xa4) != 0) {
        FUN_006063b0();  // likely updates shadow-related resources
    }

    // Toggle between two static camera matrices based on 'isPrimary' flag
    DAT_01205448 = DAT_01123f0c;
    if (isPrimary == '\0') {
        DAT_01205448 = DAT_01123f10;
    }

    // Check for additional effect (offset +0xa8)
    if (DAT_012058e8 == transformData && *(int*)((char*)transformData + 0xa8) != 0) {
        FUN_006063b0();  // update effect resources
    }

    // Copy view matrix (16 floats) into transform data at offset 0x110
    dst = (float*)((char*)transformData + 0x110);
    dst[0]  = viewMatrix[0];   dst[1]  = viewMatrix[1];   dst[2]  = viewMatrix[2];   dst[3]  = viewMatrix[3];
    dst[4]  = viewMatrix[4];   dst[5]  = viewMatrix[5];   dst[6]  = viewMatrix[6];   dst[7]  = viewMatrix[7];
    dst[8]  = viewMatrix[8];   dst[9]  = viewMatrix[9];   dst[10] = viewMatrix[10];  dst[11] = viewMatrix[11];
    dst[12] = viewMatrix[12];  dst[13] = viewMatrix[13];  dst[14] = viewMatrix[14];  dst[15] = viewMatrix[15];
    // Equivalent memcpy: *(*(int**)thisPtr + 4 + 0x110, viewMatrix, 64)

    // If this is the active camera and a shader constant buffer is present (+0x100), upload it
    if (DAT_012058e8 == transformData && *(int*)((char*)transformData + 0x100) != 0) {
        FUN_0060b020(*(int*)((char*)transformData + 0x14),  // +0x14: m_pDevice
                     *(int*)((char*)transformData + 0x100), // +0x100: m_pShaderConstantBuffer
                     (char*)transformData + 0x110);         // source: view matrix
    }

    // Copy projection matrix (16 floats) into transform data at offset 0x160
    dst = (float*)((char*)transformData + 0x160);
    dst[0]  = projMatrix[0];   dst[1]  = projMatrix[1];   dst[2]  = projMatrix[2];   dst[3]  = projMatrix[3];
    dst[4]  = projMatrix[4];   dst[5]  = projMatrix[5];   dst[6]  = projMatrix[6];   dst[7]  = projMatrix[7];
    dst[8]  = projMatrix[8];   dst[9]  = projMatrix[9];   dst[10] = projMatrix[10];  dst[11] = projMatrix[11];
    dst[12] = projMatrix[12];  dst[13] = projMatrix[13];  dst[14] = projMatrix[14];  dst[15] = projMatrix[15];

    // Upload projection matrix if active camera and second constant buffer (+0x150) exists
    if (DAT_012058e8 == transformData && *(int*)((char*)transformData + 0x150) != 0) {
        FUN_0060b020(*(int*)((char*)transformData + 0x14),
                     *(int*)((char*)transformData + 0x150),
                     (char*)transformData + 0x160);
    }
}