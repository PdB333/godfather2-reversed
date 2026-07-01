// FUNC_NAME: Camera::updateViewMatrix
// Address: 0x008cf480
// Role: Updates the camera's view/projection matrix when a dirty flag is set.
// Offsets:
//   +0x0c: Pointer to a render device object that provides matrices via vtable
//   +0x20: Dirty flag (bool) – if non‑zero, the matrix is retrieved and processed

void __fastcall Camera::updateViewMatrix() {
    // Check if the matrix needs updating (dirty flag)
    if (*(int*)(this + 0x20) != 0) {
        // Retrieve the object that can produce the current matrix
        void* renderDevice = *(void**)(this + 0x0c);
        
        // Virtual call at vtable index 0x60/4 = 0x18 – returns a pointer to 16 floats
        typedef float* (*GetMatrixFunc)();
        float* srcMatrix = ((GetMatrixFunc)(*(int**)(renderDevice)[0x18]))();
        
        // Copy the 4x4 matrix to local stack
        float matrix[16];
        for (int i = 0; i < 16; i++) {
            matrix[i] = srcMatrix[i];
        }
        
        // Process the matrix (e.g. set shader constants, combine with other matrices)
        FUN_004df720(&matrix);  // external helper function (address 0x004df720)
    }
}