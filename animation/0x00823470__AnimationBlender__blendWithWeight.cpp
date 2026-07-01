// FUNC_NAME: AnimationBlender::blendWithWeight
// Function address: 0x00823470
// Recursive interpolation/blending function for animation transformations.
// When weight is zero, applies a finalization operation (FUN_008231a0) to the source.
// Otherwise, it computes an intermediate blend (FUN_008233e0) and recurses.

typedef float Matrix44[16]; // 64 bytes, but buffer is 284 -> may include extra data like quaternion or struct padding

// Forward declarations (assuming these are engine functions)
void FUN_008231a0(void* source); // likely identity or finalize transform
void* FUN_008233e0(void* output, void* input, float blendTarget, float weight); // performs blend: output = (1-weight)*input + weight*blendTarget

void* AnimationBlender::blendWithWeight(void* dest, void* source, float weight)
{
    char tempBuffer[284]; // temporary storage for intermediate blend (284 bytes, likely a matrix + extra info)

    if (weight == 0.0f)
    {
        // Base case: apply finalization to source and return dest unchanged
        FUN_008231a0(source);
        return dest;
    }

    // Perform intermediate blend: blend source towards identity (blendTarget = 1.0f, i.e. unit/identity)
    void* intermediate = FUN_008233e0(tempBuffer, source, 1.0f, weight);

    // Recursive call with intermediate result as new source (weight unchanged? Actually recursion seems to omit third parameter
    // but the function likely uses a member or global weight; here we assume weight remains the same for simplicity)
    blendWithWeight(dest, intermediate, weight); // note: only two args shown in decompiler, maybe third is implicit via register

    return dest;
}