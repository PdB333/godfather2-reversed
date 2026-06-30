// FUNC_NAME: AnimationBlendNode::blendTransforms

// Structure for the blend context passed in param_5
struct BlendContext {
    float unknownMatrix[4]; // +0x10: some transform data (e.g., local-space rotation)
    float blendFactor;      // +0x20: interpolation factor t
    void* pHandleObject;    // +0x60: pointer to an object from which a handle can be retrieved
};

// External helper functions
extern void initLinearBlend(AnimationBlendNode* node, BlendContext* ctx);       // FUN_009e5ed0
extern void initSphericalBlend(AnimationBlendNode* node, BlendContext* ctx);     // FUN_009f5290
extern uint32_t getHandleFromObject(void* obj);                                  // FUN_004afca0
extern uint64_t someUnusedFunction(uint32_t thing);                              // FUN_00541470 (result discarded)

// Main blend function
// Parameters:
//   blendType   (param_1) - 0 = linear, else spherical
//   srcB        (param_2) - second source quaternion (first is implicit in EDI register)
//   outBlended  (param_3) - output interpolated quaternion
//   outSomething(param_4) - output copy of context->unknownMatrix
//   ctx         (param_5) - blend context with factor/transform/handle
//   outHandle   (param_6) - output handle if available
//   param7      (param_7) - flag to trigger an extra (unused) call to someUnusedFunction
// Returns 1 on success (ctx->pHandleObject != 0), 0 otherwise.
int __thiscall AnimationBlendNode::blendTransforms(
    int blendType,
    const float* srcB,       // Quaternion (4 floats)
    float* outBlended,       // Quaternion output (4 floats)
    float* outSomething,     // 4 floats output
    BlendContext* ctx,
    uint32_t* outHandle,
    int param7)
{
    // 'this' points to an AnimationBlendNode with layout:
    // +0x00: srcA (4 floats) – the first source quaternion, passed in EDI register before call
    // +0x10: srcB (4 floats)
    // +0x20: blendEnabled (byte)

    // The first source (srcA) is assumed to have been loaded into the EDI register by the caller.
    // Copy it and srcB into this node.
    this->srcA = *(const Quaternion*)unaff_EDI;   // unaff_EDI == EDI register containing srcA
    this->srcB = *(const Quaternion*)srcB;
    this->blendEnabled = 1;

    // Initialize the blending mode
    if (blendType == 0) {
        initLinearBlend(this, ctx);
    } else {
        initSphericalBlend(this, ctx);
    }

    // If a handle object exists, perform interpolation and optional handle retrieval
    if (ctx->pHandleObject != nullptr) {
        float t = ctx->blendFactor;

        // Linear interpolation (SLERP? but code shows linear) between srcA and srcB
        const float* srcA = (const float*)&this->srcA;
        outBlended[0] = (srcB[0] - srcA[0]) * t + srcA[0];
        outBlended[1] = (srcB[1] - srcA[1]) * t + srcA[1];
        outBlended[2] = (srcB[2] - srcA[2]) * t + srcA[2];
        outBlended[3] = (srcB[3] - srcA[3]) * t + srcA[3];

        // Copy the unknown matrix from context
        outSomething[0] = ctx->unknownMatrix[0];
        outSomething[1] = ctx->unknownMatrix[1];
        outSomething[2] = ctx->unknownMatrix[2];
        outSomething[3] = ctx->unknownMatrix[3];

        // Optional side effect: call a function with obj->field_0x1c and discard result
        if (param7) {
            uint32_t objField = *(uint32_t*)((uint8_t*)ctx->pHandleObject + 0x1c);
            uint64_t dummy = someUnusedFunction(objField);
            // The compiler wrote part of the result back, but it's unused
            // *(uint32_t*)((uint8_t*)&dummy + 4) = (uint32_t)dummy;
        }

        // Retrieve handle from the object if requested
        if (outHandle != nullptr) {
            *outHandle = getHandleFromObject(ctx->pHandleObject);
        }
        return 1;
    }

    // No handle object – just set handle to 0 if requested and return failure
    if (outHandle != nullptr) {
        *outHandle = 0;
    }
    return 0;
}