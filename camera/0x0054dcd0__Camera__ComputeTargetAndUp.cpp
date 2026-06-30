// FUNC_NAME: Camera::ComputeTargetAndUp
// Address: 0x0054dcd0
// This function computes two vectors (likely target and up vectors for a camera) from an internal orientation state.
// The internal state is obtained via a virtual call on the object at this+0x18.
// The constant 0xe2cd54 is a scaling factor (mogelijke 0.5f or similar).
// Stack layout: local_30, fStack_2c, fStack_24, fStack_20, fStack_1c are interpreted as components of two vectors.

void __thiscall Camera::ComputeTargetAndUp(float* outTarget, float* outUp)
{
    // Fetch orientation data via virtual call on the sub-object at offset +0x18
    // Virtual function at vtable index 0x18 (relative to sub-object's vtable)
    void* subObj = *(void**)(this + 0x18);               // +0x18: pointer to sub-object (e.g., rotation component)
    void (__thiscall* fetchFunc)(void*) = *(void (__thiscall**)(void*))(*(int*)subObj + 0x18);
    fetchFunc(subObj);  // This call fills stack locals with orientation data (5 floats)

    // Assume local variables represent two vectors:
    // VecA: (local_30, fStack_2c, fStack_24)   [might be forward vector]
    // VecB: (fStack_20, fStack_1c, ???)         [might be up vector, but only 2 components? Actually 5 floats total]
    // The decompiler may have mislabeled due to alignment; we treat them as contiguous stack floats.

    // Reinterpret stack variables as separate floats for clarity (names based on stack offsets from ebp)
    float a0 = /*local_30*/ ;  // -0x30
    float a1 = /*fStack_2c*/ ; // -0x2c
    float a2 = /*fStack_24*/ ; // -0x24
    float b0 = /*fStack_20*/ ; // -0x20
    float b1 = /*fStack_1c*/ ; // -0x1c

    // Global scaling factor (likely 0.5f or something)
    float scale = DAT_00e2cd54;  // Address 0x00e2cd54

    // Compute intermediate values
    float fVar1 = (a2 + a0) * scale;   // (a2 + a0) -- note: this assumes a0 is used as first component? Actually decompiler used (fStack_24 + (float)&local_30) which is weird. 
    float fVar2 = (b0 + a0) * scale;   // (fStack_20 + local_30)
    float fVar3 = (b1 + a1) * scale;   // (fStack_1c + fStack_2c)

    // Fill output vectors
    outTarget[0] = a0 - fVar1;
    outTarget[1] = a0 - fVar2;   // Note: decompiler used local_30 (same as a0) for both target[0] and target[1]? Actually second target component uses local_30 again.
    outTarget[2] = a1 - fVar3;   // fStack_2c - fVar3

    outUp[0] = a2 - fVar1;
    outUp[1] = b0 - fVar2;
    outUp[2] = b1 - fVar3;
}