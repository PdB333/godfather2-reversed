// FUNC_NAME: AnimBlendNode::blendAndScaleTransform

void AnimBlendNode::blendAndScaleTransform(void *this, float blendWeight, float *outputMatrix) {
    float *inputTransform; // unaff_ESI - pointer to source transform (16 floats)
    int someState; // iVar2
    int somePointer; // uVar1

    somePointer = *(int *)(*(int *)(this + 0x50) + 0x90);
    someState = *(int *)(this + 0x58);
    if ((someState != 0) && ((*(byte *)(*(int *)(this + 0x10) + 0x104) & 1) != 0)) {
        // Store original transform state if blending is active
        *(uint *)(someState + 0x94) &= 0xfffffff7; // clear some bit flag
        *(undefined8 *)(someState + 0x80) = *(undefined8 *)(inputTransform + 0xc); // two floats from input[12..13]
        *(ulonglong *)(someState + 0x88) = CONCAT44(blendWeight, inputTransform[0xe]); // blendWeight, input[14]
        FUN_0044f770(*(int *)(this + 0x58), 0);
    }

    // Scale the first 12 floats (the rotation/scale part of the 4x4 matrix) by blendWeight
    float scaledTransform[16];
    scaledTransform[0]  = inputTransform[0]  * blendWeight;
    scaledTransform[1]  = inputTransform[1]  * blendWeight;
    scaledTransform[2]  = inputTransform[2]  * blendWeight;
    scaledTransform[3]  = inputTransform[3]  * blendWeight;
    scaledTransform[4]  = inputTransform[4]  * blendWeight;
    scaledTransform[5]  = inputTransform[5]  * blendWeight;
    scaledTransform[6]  = inputTransform[6]  * blendWeight;
    scaledTransform[7]  = inputTransform[7]  * blendWeight;
    scaledTransform[8]  = inputTransform[8]  * blendWeight;
    scaledTransform[9]  = inputTransform[9]  * blendWeight;
    scaledTransform[10] = inputTransform[10] * blendWeight;
    scaledTransform[11] = inputTransform[11] * blendWeight;
    scaledTransform[12] = inputTransform[12];          // translation unchanged
    scaledTransform[13] = inputTransform[13];
    scaledTransform[14] = inputTransform[14];
    scaledTransform[15] = inputTransform[15];

    // Call some preprocessing function on outputMatrix
    FUN_00433950(outputMatrix);

    // Compute blend mode flags from a control word at this+0x10->+0x108
    int controlFlags = *(int *)(*(int *)(this + 0x10) + 0x108);
    int blendMode = (~(controlFlags >> 0x1a) & 4) | 2; // bits 26-31, inverted, or with 2

    // Apply scaled transform with blending
    FUN_00433700(somePointer, scaledTransform, 0, inputTransform[0x10], blendMode, 0);
}