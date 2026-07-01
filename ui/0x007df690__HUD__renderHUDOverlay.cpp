// FUNC_NAME: HUD::renderHUDOverlay
void HUD::renderHUDOverlay(void)
{
    int *pSomeObject;           // Pointer to some game object (e.g., player HUD data)
    int *pCameraMatrixData;     // Pointer to camera matrix data (e.g., view/projection)
    int *pMatrixRowData;        // Second camera matrix pointer for reading rows
    undefined8 local_60;        // Might be float3 for position/scale
    undefined4 local_58;        // Part of the same vector
    undefined8 local_54;        // Second float3
    undefined4 local_4c;        // Part
    undefined8 local_48;        // Third float3
    undefined4 local_40;        // Part
    int iObjectState;           // State field value (0x48 = e.g., HUD hidden)
    int iDrawIndex;             // Computed draw index (offset into HUD element list)

    // Get pointer to some object from global context (e.g., g_pGameManager + 4)
    pSomeObject = **(int **)(DAT_012233a0 + 4); // DAT_0x012233a0 likely points to global game context

    if ( (pSomeObject != NULL) &&
         ( (pSomeObject - 0x1F30) != NULL) && // Base pointer check
         (*(int *)(pSomeObject + 0x1190) != 0) && // State field != 0
         (*(int *)(pSomeObject + 0x1190) != 0x48) ) // State not equal to 0x48 (=72, e.g., HUD disabled)
    {
        // Get camera matrix pointer (returns pointer to a matrix structure)
        pCameraMatrixData = (int *)FUN_00471610(); // e.g., getCameraMatrix()
        // Get a second pointer to the same matrix for reading partial rows
        pMatrixRowData = (int *)FUN_00471610();    // e.g., getCameraMatrix() again

        // Read three rows (or vectors) from the matrix data
        // Each row is stored as 8 bytes (two floats) + 4 bytes (one float) — 12 bytes total
        local_48 = pMatrixRowData[4];          // Row 3? (offset 32)
        local_40 = *(undefined4 *)(pMatrixRowData + 5); // Part of row 3 (offset 40)
        local_54 = *pMatrixRowData;           // Row 0 (offset 0)
        local_4c = *(undefined4 *)(pMatrixRowData + 1); // Part of row 0 (offset 8)
        local_60 = pMatrixRowData[2];         // Row 2 (offset 16)
        local_58 = *(undefined4 *)(pMatrixRowData + 3); // Part of row 2 (offset 24)

        // Determine draw index based on state field
        if (*(int *)(pSomeObject + 0x1190) == 0) {
            iDrawIndex = 0;
        } else {
            iDrawIndex = *(int *)(pSomeObject + 0x1190) - 0x48; // Subtract 72 to get index
        }

        // Render the HUD element (e.g., a sprite or reticle)
        // Arguments: base pointer, index, 1, two globals (e.g., screen size), camera data + offset,
        // and the three reading rows (likely representing world-to-screen transform)
        FUN_00852c80( pSomeObject - 0x1F30,          // Base of HUD element storage
                      iDrawIndex,                    // Which element to draw
                      1,                             // Always 1
                      DAT_00d5e288,                  // Global (e.g., screen width)
                      DAT_00d5e288,                  // Global (e.g., screen height)
                      pCameraMatrixData + 0x30,      // Additional camera data (e.g., projection matrix)
                      &local_48,                     // Matrix row 3
                      &local_54,                     // Matrix row 0
                      &local_60,                     // Matrix row 2
                      0, 0, 1 );                     // Extra parameters (maybe color, depth, etc.)

        // End HUD drawing (e.g., pop state, restore matrices)
        FUN_00853df0();
    }
}