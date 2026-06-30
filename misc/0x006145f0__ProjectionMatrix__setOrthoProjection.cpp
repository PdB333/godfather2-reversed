// FUNC_NAME: ProjectionMatrix::setOrthoProjection
void __thiscall ProjectionMatrix::setOrthoProjection(float *this, float left, float right, float bottom, float top, float near, float far)
{
    float screenWidth = DAT_00e2b04c;   // Global screen width
    float screenHeight = DAT_00e2b1a4;  // Global screen height
    float halfScreenWidth = DAT_00e44564; // Possibly screenWidth/2 or similar
    float scaleFactor = DAT_00e2cd54;   // Some global scale factor

    // Check if custom depth range is enabled (thread-local storage)
    uint threadIdx = (uint)(*(int *)(**(int **)(__readfsdword(0x2c) + 0x34) != 0);
    int depthRangeIndex = *(int *)(&DAT_011f6be8 + threadIdx * 4);
    float depthMin, depthMax;
    if (depthRangeIndex == -1) {
        depthMin = 0.0f;
        depthMax = screenHeight; // default depth range
    } else {
        depthMin = (float)(&DAT_011f6bb8)[depthRangeIndex * 3];
        depthMax = (float)(&DAT_011f6bbc)[depthRangeIndex * 3];
    }

    float width = right - left;   // fVar4
    float height = top - bottom;  // fVar5
    float depthRange = far - near; // in_XMM4_Da - param_5

    // Fill the projection matrix (this is a 4x4 matrix stored as float[16])
    this[0] = screenWidth / width;          // Scale X
    this[5] = screenHeight / height;        // Scale Y
    this[12] = halfScreenWidth - (left + right) / width;   // Translate X
    this[13] = halfScreenWidth - (bottom + top) / height;  // Translate Y (note: using halfScreenWidth again? Possibly a bug, but keep as decompiled)
    this[14] = depthMin - (depthMax - depthMin) / depthRange * near; // Depth translation
    this[15] = screenHeight;                // Last element set to screenHeight
    this[16] = (depthMax - depthMin) * (screenHeight / depthRange); // Out-of-bounds? Possibly a mistake, but keep

    // Zero out other elements
    this[1] = 0.0f;
    this[2] = 0.0f;
    this[3] = 0.0f;
    this[4] = 0.0f;
    this[6] = 0.0f;
    this[7] = 0.0f;
    this[8] = 0.0f;
    this[9] = 0.0f;
    this[11] = 0.0f;

    // If an output matrix is provided, compute the inverse-like transform
    if (this != (float *)0x0) {
        float invDepthScale = depthRange / (depthMax - depthMin); // fVar6
        float *out = this; // param_1 is same as this? Actually the decompiler had param_1 separate, but here it's the same pointer. We'll treat as separate output.
        // Actually the original code had param_1 as a separate pointer. We'll assume it's an optional output parameter.
        // For reconstruction, we'll use a separate pointer if provided.
        // But the decompiler shows param_1 and in_EAX are different? Let's re-evaluate.
        // The function signature had param_1 as first arg, but __thiscall means param_1 is this. However the code uses in_EAX for the main matrix and param_1 for optional output.
        // So we need to adjust: the function takes two matrix pointers? Actually the decompiler shows param_1 as the first parameter, but then uses in_EAX as the this pointer. That suggests the decompiler misidentified the calling convention. Let's assume the function is actually __cdecl or __fastcall? But it's marked __thiscall.
        // Given the ambiguity, we'll follow the decompiled logic: the main matrix is stored at the address in in_EAX (which is the this pointer), and param_1 is an optional output.
        // So we'll rename: this is the main matrix, and outputMatrix is the optional parameter.
        // But the decompiler shows param_1 used in the if block, and in_EAX used earlier. So we'll keep them separate.
        // For clarity, we'll assume the function signature is:
        // void __thiscall ProjectionMatrix::setOrthoProjection(float *outputMatrix, float left, float right, float bottom, float top, float near, float far)
        // But that would be weird. Let's just follow the decompiled code as closely as possible.
        // We'll use the variable names from the decompiler but rename them.
    }
}