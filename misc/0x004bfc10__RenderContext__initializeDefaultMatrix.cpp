// FUNC_NAME: RenderContext::initializeDefaultMatrix
void __thiscall RenderContext::initializeDefaultMatrix(int deviceContext, int renderTarget, int format, int flags)
{
    // Base initialization (likely calls parent class constructor)
    FUN_004bfcf0();

    // Acquire a render resource handle (e.g., shader program, texture, or buffer)
    int resourceHandle = FUN_0045b570(deviceContext, renderTarget, format, flags);

    // +0x90: Store the resource handle
    *(int *)(this + 0x90) = resourceHandle;

    // Global constant representing 1.0f as integer (likely 0x3F800000)
    int one = DAT_00e2b1a4;

    // +0x40 to +0x7C: 4x4 matrix (16 floats, 64 bytes), stored row-major
    // Set diagonal elements to 1.0, all others to 0.0 -> identity matrix
    // Indices: (0,0), (1,1), (2,2), (3,3)
    *(int *)(this + 0x40) = one;   // matrix[0][0]
    *(int *)(this + 0x44) = 0;     // matrix[0][1]
    *(int *)(this + 0x48) = 0;     // matrix[0][2]
    *(int *)(this + 0x4c) = 0;     // matrix[0][3]

    *(int *)(this + 0x50) = 0;     // matrix[1][0]
    *(int *)(this + 0x54) = one;   // matrix[1][1]
    *(int *)(this + 0x58) = 0;     // matrix[1][2]
    *(int *)(this + 0x5c) = 0;     // matrix[1][3]

    *(int *)(this + 0x60) = 0;     // matrix[2][0]
    *(int *)(this + 0x64) = 0;     // matrix[2][1]
    *(int *)(this + 0x68) = one;   // matrix[2][2]
    *(int *)(this + 0x6c) = 0;     // matrix[2][3]

    *(int *)(this + 0x70) = 0;     // matrix[3][0]
    *(int *)(this + 0x74) = 0;     // matrix[3][1]
    *(int *)(this + 0x78) = 0;     // matrix[3][2]
    *(int *)(this + 0x7c) = one;   // matrix[3][3]

    // Finalize initialization (e.g., set render state flags)
    FUN_006101b0();
    return;
}