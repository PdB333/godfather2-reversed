// FUNC_NAME: SomeTransform::extractAxes
void __thiscall SomeTransform::extractAxes(float *outVec1, float *outVec2)
{
    // Call virtual function to fill internal matrix/vectors (stack locals)
    // +0x18 is a pointer to a subobject, +0x18 of that is a virtual function
    (**(code **)(**(int **)(this + 0x18) + 0x18))();

    // Stack variables filled by the call; interpreted as two 3-vectors or matrix rows
    // Layout likely: [0] = a0, [1] = a1, [2] = a2, [3] = b0, [4] = b1, [5] = b2 (but one missing in decomp)
    float a0 = local_30;          // +0x00
    float a1 = fStack_2c;        // +0x04
    float a2 = fStack_24;        // +0x0C? (gap due to missing slot)
    float b0 = fStack_20;        // +0x10
    float b1 = fStack_1c;        // +0x14

    // Constant from global data
    float scale = DAT_00e2cd54;

    // Intermediate sums (component-wise addition of two vectors)
    float t0 = (a2 + a0) * scale;  // uses a2 and a0
    float t1 = (b0 + a0) * scale;  // uses b0 and a0
    float t2 = (b1 + a1) * scale;  // uses b1 and a1

    // Output vectors = original - weighted sum
    outVec1[0] = a0 - t0;   // was (float)&local_30 - fVar1; pointer used as value due to decompilation artifact
    outVec1[1] = a0 - t1;   // originally used local_30 again, likely a mis-index; assuming a0
    outVec1[2] = a1 - t2;   // was fStack_2c - fVar3

    outVec2[0] = a2 - t0;   // was fStack_24 - fVar1
    outVec2[1] = b0 - t1;   // was fStack_20 - fVar2
    outVec2[2] = b1 - t2;   // was fStack_1c - fVar3
}