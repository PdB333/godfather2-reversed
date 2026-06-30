// FUNC_NAME: DebugRenderable::drawDebugInfo
void DebugRenderable::drawDebugInfo() {
    char matrix[8];          // 8-byte transformation matrix (2x2 or quaternion)
    int color;               // Color from global constant (+0x00e2cd48)
    int zero1;               // Padding or second component
    int zero2;               // Padding or third component

    // Check if debug visualization is enabled (offset +0xA8)
    if (*(int*)(this + 0xA8) != 0) {
        // Retrieve transformation matrix from object at this+0x8 and a secondary structure
        FUN_00c9cbe0(
            *(int*)(this + 0x8),                       // Source object pointer
            *(int*)(*(int*)(this + 0xA4) + 0x10),    // Offset into another structure
            0,                                        // Parameter (unused)
            matrix                                    // Output matrix
        );

        // Set color from global constant
        color = DAT_00e2cd48;
        zero1 = 0;
        zero2 = 0;

        // Begin rendering
        FUN_00c9eac0();

        // Set texture/shader state
        FUN_00ca4e90(0, 0);

        // Draw debug geometry using the matrix
        FUN_00c9cd40(0, matrix);

        // End rendering
        FUN_00c9eae0();
    }
}