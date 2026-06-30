// FUNC_NAME: RenderManager::applyDistortion
// Function address: 0x00418c50
// Applies lens distortion correction to a 3D position (param_1) using a rational distortion model.
// Uses thread-local storage to retrieve application data (likely screen bounds) and global distortion coefficients.
// Calls render manager virtual methods to set distortion parameters.

// Globals:
extern uint8_t gDistortionEnabled;           // DAT_0120587e - enable flag for distortion
extern void* gRenderManager;                 // DAT_01205750 - pointer to render manager instance (vtable at +0xe4)
extern float gDistortionMatrix[16];          // _DAT_011f69f8, _DAT_011f6a08, etc. (4x4 transformation matrix)
extern float gDistortionCoeffA;              // _DAT_011f6a58
extern float gDistortionCoeffB;              // _DAT_011f6a68
extern float gDistortionCoeffC;              // _DAT_011f6a5c
extern float gDistortionCoeffD;              // _DAT_011f6a6c

// Access via FS segment: +0x2c -> TLS pointer, +0x24 offset gives app data block
#define GET_TLS_APPDATA() (*(int*)(*(int*)(__readfsdword(0x2c) + 0x24)))

void __fastcall RenderManager::applyDistortion(float* position, float tolerance)
{
    uint8_t enabled = gDistortionEnabled;
    if (enabled == 0) return;

    // Retrieve app data pointer from TLS, then extract two bounds (likely screen width/height or near/far planes)
    int appDataPtr = GET_TLS_APPDATA();
    float boundLow  = *(float*)(appDataPtr + 0x144);   // +0x144 - lower bound
    float boundHigh = *(float*)(appDataPtr + 0x148);   // +0x148 - upper bound

    // Transform input position (3-element vector) by the distortion matrix (first row)
    float transformed = position[0] * gDistortionMatrix[0]
                      + position[1] * gDistortionMatrix[4]
                      + position[2] * gDistortionMatrix[8]
                      + gDistortionMatrix[12];   // homogeneous bias

    // Apply tolerance to produce a range [lowVal, highVal]
    float lowVal  = transformed - tolerance;
    float highVal = transformed + tolerance;

    // Clamp lowVal and highVal to [boundLow, boundHigh] using confused but functional clamping logic
    float clampedLow = boundLow;
    if (boundLow < lowVal) {
        clampedLow = lowVal;
        if (boundHigh <= lowVal) {
            clampedLow = boundHigh;
        }
    }
    float clampedHigh = boundHigh;  // Actually boundHigh initially, but used for high side after swap? 
    // Note: The decompiler reversed roles; in the next block they modify boundLow/boundHigh variables.
    // We'll rename to outLow, outHigh for clarity.

    // The second clamp uses the same pattern but with highVal and swapped initial values
    // In original: fVar3 starts as boundLow, then condition modifies to highVal, then possibly to boundHigh.
    // That mirrors the first block but with highVal.
    float outLow = boundLow;
    if (boundLow < highVal) {
        outLow = highVal;
        if (boundHigh <= highVal) {
            outLow = boundHigh;
        }
    }

    // Compute rational distortion coefficients for both clamped values
    // f(var) = (A*var + B) / (C*var + D)
    float distLow  = (gDistortionCoeffA * clampedLow + gDistortionCoeffB)
                   / (gDistortionCoeffC * clampedLow + gDistortionCoeffD);
    float distHigh = (gDistortionCoeffA * outLow + gDistortionCoeffB)
                   / (gDistortionCoeffC * outLow + gDistortionCoeffD);

    // Notify render manager via virtual call at vtable+0xe4
    // First call: set distortion range low/high (msg 0xb6 with two floats)
    typedef void (__thiscall* SetDistortionFunc)(void* self, int msg, float val1, float val2, float val3);
    SetDistortionFunc setDistortion = (SetDistortionFunc)(*(int**)gRenderManager)[0x39]; // +0xe4 / 4 = 0x39

    setDistortion(gRenderManager, 0xB6, distLow, distLow, distHigh);  // 0xB6: low-coefficient for both? Not clear, but matches original

    // Second call: set another parameter (msg 0xB7) with integer 0xB6 as a float (likely a misinterpretation, 
    // but kept for consistency; may actually be a float derived from previous computation)
    setDistortion(gRenderManager, 0xB7, 0xB6);   // 0xB7: some integer parameter (182)

    // Third call: set a constant (msg 0xB4) with value 49.084f (often near-plane or FOV conversion)
    setDistortion(gRenderManager, 0xB4, 49.084f); // 0xB4: e.g., near plane distance
}