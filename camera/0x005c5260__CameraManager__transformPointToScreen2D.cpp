// FUNC_NAME: CameraManager::transformPointToScreen2D
// Address: 0x005c5260
// Converts a 2D point using camera transform and global scaling constants.
// The function fills two output floats (likely screen coordinates) by combining
// results from two subroutines with global scale factors.

void CameraManager::transformPointToScreen2D(float *outX, float *outY)
{
    // Call helper functions to fill local transform matrix.
    // These likely retrieve the current camera projection or viewport parameters.
    FUN_005c4850(); // Possibly getCameraProjectionMatrix or similar
    FUN_00417560(); // Possibly getViewportTransform or similar

    // Stack layout: a 2x4 matrix (row-major) filled by the above calls.
    // Rows: row0[0..3] and row1[0..3]
    float row0[4]; // rows are interleaved in the original memory: row0[0]=local_50, row0[1]=local_40, row0[2]=local_30, row0[3]=local_20
    float row1[4]; // row1[0]=uStack_4c, row1[1]=uStack_3c, row1[2]=uStack_2c, row1[3]=uStack_1c

    // Global constants (likely viewport width/height or zoom factors)
    const float globalScaleX = DAT_00e2fc48; // +0x0? (address in data section)
    const float globalScaleY = DAT_00e2b1a4; // +0x0? (another global)

    // Compute output as linear combination of the last two columns of each row
    // Effectively: input vector = (0, 0, globalScaleX, globalScaleY)
    *outX = row0[0] * 0.0f + row0[1] * 0.0f + globalScaleX * row0[2] + globalScaleY * row0[3];
    *outY = row1[0] * 0.0f + row1[1] * 0.0f + globalScaleX * row1[2] + globalScaleY * row1[3];
}