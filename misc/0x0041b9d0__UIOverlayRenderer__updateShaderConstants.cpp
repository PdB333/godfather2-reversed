// FUNC_NAME: UIOverlayRenderer::updateShaderConstants
// Address: 0x0041b9d0
// Update shader uniform for UI overlay based on scale and offset values.

extern "C" void FUN_00419370();  // Returns object pointer in EDX
extern "C" void FUN_00417560();  // Prepares render transform
extern "C" void FUN_0056b0e0(void*, void*, float*); // Sets shader uniform (vec4)

// Global constants (likely from .rdata section)
extern float g_constA; // DAT_00e2b1a4
extern float g_constB; // DAT_01205354
extern float g_constC; // DAT_00e2b04c
extern float g_constD; // DAT_00e44564

// Global shader program handles
extern void* g_shaderProgA; // DAT_01163610
extern void* g_shaderProgB; // DAT_011629d0

class UIOverlayRenderer {
public:
    void updateShaderConstants(int transformPtr) {
        // Check if overlay is enabled (byte at offset 0x0C)
        if (*(char*)(this + 0x0C) == 0)
            return;

        // Get base object from engine
        int baseObj = (int)FUN_00419370();

        // Compute offset to the data block
        int offset = *(int*)(baseObj + 8) + *(int*)(transformPtr + 0x18);

        // Read scale and offset values from the data block
        float scale = *(float*)(offset + 0x70) * g_constB;
        float intermediate = scale * g_constC + *(float*)(offset + 0x6C);
        float constant = g_constA;

        // Unused variable: float screenHeight = g_constD; (calculated but not used)

        // Prepare rendering state
        FUN_00417560();

        // Build uniform (4 floats)
        float uniform[4];
        uniform[0] = constant / scale;
        uniform[1] = constant / scale; // Same as first component
        uniform[2] = constant / intermediate;
        uniform[3] = 0.0f;

        // Set shader uniform (likely a vec4)
        FUN_0056b0e0(g_shaderProgA, g_shaderProgB, uniform);
    }
};