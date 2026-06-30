// FUNC_NAME: TransformComponent::setMatrixWithClamp
// Address: 0x005037e0
// Copies a 4x4 matrix from a source (passed in EAX) to an object's matrix field at offset 0x40.
// If the first three elements' magnitude (a vector) is within [g_minMatrixScale, g_maxMatrixScale],
// it just copies and calls FUN_00424470 (likely an identity or validation callback).
// Otherwise, it scales the matrix by g_defaultMatrixScale / magnitude and stores the scaled result
// at offset 0x80, using FUN_0056b0e0 (a matrix scaling function).

// Global constants from data references
extern float g_minMatrixScale;      // DAT_00e44854
extern float g_maxMatrixScale;      // DAT_00e4488c
extern float g_defaultMatrixScale;  // DAT_00e2b1a4

// External helper functions
void FUN_00424470(); // unknown: possibly sets matrix to identity or triggers action
void FUN_0056b0e0(float* matrix, float* out, float* scale); // scales matrix by uniform factor

void __fastcall TransformComponent::setMatrixWithClamp(void* unusedECX, int obj)
{
    // Source matrix pointer is passed via EAX register (not a standard parameter).
    // For proper reconstruction, we treat it as an implicit input.
    float* src; // actually the source pointer in EAX

    // Copy 16 floats from src to obj's matrix at offset 0x40.
    // Offsets: +0x40 through +0x7c (contiguous 4x4 float matrix)
    float* dstMat = (float*)(obj + 0x40);
    for (int i = 0; i < 16; ++i) {
        dstMat[i] = src[i];
    }

    // Compute magnitude of the first three elements (likely translation or orientation vector)
    float magnitude = sqrtf(src[0]*src[0] + src[1]*src[1] + src[2]*src[2]);

    // Check if magnitude is within allowed range
    if ((g_minMatrixScale <= magnitude) && (magnitude <= g_maxMatrixScale)) {
        // Within range: just copy and call the callback
        FUN_00424470();
        return;
    }

    // Scale factor: default scale divided by magnitude
    float scaleFactor = g_defaultMatrixScale / magnitude;

    // Apply uniform scaling to the copied matrix and store result at obj + 0x80
    FUN_0056b0e0(dstMat, (float*)(obj + 0x80), &scaleFactor);
}