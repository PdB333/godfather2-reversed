// FUNC_NAME: DebugDrawTransform
void __thiscall DebugDrawTransform(void* thisPtr) {
    // Check if there is a drawable object (non-null pointer at +0xA8)
    if (*(void**)((char*)thisPtr + 0xA8) != 0) {
        // 8-byte buffer for transform data (e.g., a quaternion or 2D vector)
        char transformBuffer[8];

        // Compute world transform from entity ID (+0x8) and matrix data
        // The matrix is obtained by dereferencing pointer at +0xA4 and adding offset 0x10
        // Arguments: (entityID, matrixData, 0, transformBuffer)
        FUN_00c9cbe0(
            *(int*)((char*)thisPtr + 0x8),
            *(int*)(*(int*)((char*)thisPtr + 0xA4) + 0x10),
            0,
            transformBuffer
        );

        // Prepare rendering state (color from global, position from +0x38, zero)
        int color = DAT_00e2cd48;   // Global color/constant
        int position = *(int*)((char*)thisPtr + 0x38); // Offset +0x38 likely a world position or color
        int zero = 0;

        // Begin rendering (push matrix)
        FUN_00c9eac0();

        // Set alpha/color (arg0=0, arg1=1.0f)
        FUN_00ca4e90(0, 1.0f);

        // Draw geometry using the computed transform
        FUN_00c9cd40(0, transformBuffer);

        // End rendering (pop matrix)
        FUN_00c9eae0();
    }
}