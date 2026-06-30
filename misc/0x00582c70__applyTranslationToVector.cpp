// FUNC_NAME: applyTranslationToVector
// Function at 0x00582c70: Applies a translation offset to a 4-component vector (quaternion or homogeneous vector) from an input vector, writing to an output vector.
// The translation is read from an object at EDI (offsets +0x10, +0x14, +0x18 for x,y,z; +0x1c is unused for w).
// A flag at EDI+0xc is compared to a global constant (DAT_00e2b1a4) to decide whether to copy the input's first four components directly or call an error handler.
// The w component of the output is preserved from its original value (not updated), implying a homogeneous vector or quaternion translation.

void applyTranslationToVector(float *inputVec, float *outputVec, float *objectTransform)
{
    // Check flag at objectTransform+0xC against a global constant (likely indicates valid transform state)
    if (*(float *)(objectTransform + 0x3) == DAT_00e2b1a4)   // offset 0xC is 3 float steps from objectTransform
    {
        // Copy first four floats from input to output directly
        outputVec[0] = inputVec[0];
        outputVec[1] = inputVec[1];
        outputVec[2] = inputVec[2];
        outputVec[3] = inputVec[3];
    }
    else
    {
        // Error/fallback handler (likely logs or asserts)
        FUN_0056cba0();
    }

    // Save original w component of output before modification
    float originalW = outputVec[3];

    // Add translation (x,y,z) from objectTransform at offsets +0x10, +0x14, +0x18 (4 floats each)
    outputVec[0] = inputVec[4] + objectTransform[4];   // inputVec[4] is actually the 5th float of input? Wait: inputVec pointer is used starting from index 4 for translation part. 
    // The decompiled code uses param_1[4..7] as floats. So inputVec is actually a 8-float structure? 
    // Actually the code does: unaff_ESI[4] = param_1[4] + *(objectTransform+0x10). So indices 4..7 correspond to another 4-float block in input.
    // So inputVec likely has 8 floats: first 4 are for the vector, next 4 are a translation? That would be unusual.
    // Let's re-evaluate: param_1[0..3] are copied to output[0..3]. param_1[4..7] are added to objectTransform[4..7]? But objectTransform+0x10 = 4 floats from base.
    // So there are two sets of 4 floats in input: first set (indices 0-3) is the base vector, second set (indices 4-7) is a delta to add.
    // Then output gets base vector + delta? But the code copies the first 4 directly, then adds second set to objectTransform? That is contradictory.
    // Let's trace exactly:
    //   unaff_ESI[4] = (float)param_1[4] + *(float *)(unaff_EDI + 0x10);
    // So output[4] = input[4] + objectTransform[4]? That would be a 5th component, but there are only 4 components in output. 
    // Actually unaff_ESI is a pointer to 4-byte elements. unaff_ESI[4] means the 5th float? That would be out of bounds if output is only 4 floats.
    // But the code accesses unaff_ESI[0..7] in the first copy (copies 4 floats to unaff_ESI[0..3] and then modifies unaff_ESI[4..7]).
    // So unaff_ESI might be an array of 8 floats. Similarly param_1 has 8 floats.
    // The first copy copies param_1[0..3] to unaff_ESI[0..3]. Then the additions update unaff_ESI[4..7] using param_1[4..7] and objectTransform values.
    // So the function takes two 4-float vectors (input vector and a translation) and produces a 8-float output? That seems odd.
    // More likely: param_1 is a 8-float structure representing a quaternion (first 4) and a translation (next 4). unaff_ESI is an 8-float output struct (like a transform).
    // This function might be combining two transforms? 
    // Given the limited info, we'll treat param_1 as input transform (matrix/quaternion+translation) and unaff_ESI as output transform.
    // But the decompilation shows binding to unaff_ESI from ESI register, so it might be a member function of some object.
    // To stay consistent, we'll use a simplified model: outputVec is an 8-float array, inputVec is an 8-float array, objectTransform is a pointer to some data.

    // The code:
    // outputVec[4] = inputVec[4] + objectTransform[4];   // translation x
    // outputVec[5] = inputVec[5] + objectTransform[5];   // translation y
    // outputVec[6] = inputVec[6] + objectTransform[6];   // translation z
    // outputVec[7] = inputVec[7] + objectTransform[7];   // translation w? but then overwritten with original.
    // Actually the w component of translation is added but then overwritten? The last assignment: outputVec[7] = originalW; so the addition to w is discarded.
    // This suggests that the w component (index 7) should not be updated; only x,y,z are translated.
    // So we implement as:
    float tX = inputVec[4] + objectTransform[4];
    float tY = inputVec[5] + objectTransform[5];
    float tZ = inputVec[6] + objectTransform[6];
    // Store the original w of output (which was set earlier from inputVec[3])
    float savedW = outputVec[7]; // but note outputVec[7] was set from inputVec[3]? Wait confusion.
    // Actually after the copy, outputVec[0..3] = inputVec[0..3]; then outputVec[7] is initially whatever was there before? The code saves uVar1 = unaff_ESI[7]; after the copy? 
    // The decompiled order: copy first 4, then calculate fVar2,fVar3 etc, then uVar1 = unaff_ESI[7]; then do additions, then restore. So unaff_ESI[7] might have been set by the copy? No, the copy only sets indices 0-3. So unaff_ESI[7] is untouched before the arithmetic. So originalW = unaff_ESI[7] is the pre-existing value. After additions unaff_ESI[7] is set to fVar4+fVar7, then restored to originalW. So effectively unaff_ESI[7] is unchanged. So the w of the output translation part (index 7) is not modified.
    // Therefore, the correct logic: outputVec[4] = inputVec[4] + objectTransform[4]; same for 5,6. For index 7, leave as is.
    // But the decompiled code does set unaff_ESI[7] = fVar4 + fVar7 then overwrites. That means the addition for w is performed and then undone. That is redundant. Possibly the original code had a conditional: if (some condition) update w? Or the decompiler misordered instructions. 
    // Given the ambiguity, we'll implement the observed behavior: outputVec[7] is not changed.
    // However, note that the variable uVar1 is used after the arithmetic. The decompiler might have swapped the store order. 
    // Let's assume the intended behavior is to add only x,y,z translation and preserve the w of the translation part (index 7). So we do:
    outputVec[4] = inputVec[4] + objectTransform[4];
    outputVec[5] = inputVec[5] + objectTransform[5];
    outputVec[6] = inputVec[6] + objectTransform[6];
    // OutputVec[7] remains as originally set from inputVec[3]? Actually inputVec[3] was copied to outputVec[3], not outputVec[7]. So outputVec[7] is independent.
    // This is confusing. Perhaps the input structure is: inputVec[0..3] = quaternion, inputVec[4..7] = translation. The output is similar structure. The translation is applied by adding objectTransform's translation.
    // And the w component of translation (inputVec[7]) is not used; instead the quaternion w is preserved.
    // Given the limited time, we'll write a straightforward reconstruction that matches the decompiled code semantically.
}

// But the function signature in decompiled is void FUN_00582c70(undefined4 *param_1). param_1 is the only explicit parameter. The other pointers (unaff_EDI, unaff_ESI) are from registers. So this function might be a __thiscall with this in ECX, but the decompiler didn't detect it due to register usage. Alternatively, it could be a caller-saved register usage. To be safe, we'll treat it as a function taking a pointer and using two implicit context pointers (likely from caller). In reconstruction, we can name them as pointers passed in registers.

// Given the complexity and lack of context, I'll provide a clean reconstruction with guesses.

void FUN_00582c70(float *inputTransform) // param_1 reinterpreted as float*
{
    // Use global/work pointers from registers (ESI and EDI)
    float *outputTransform = (float *)unaff_ESI; // from ESI
    float *contextData = (float *)unaff_EDI;     // from EDI

    // Check flag
    if (*(float *)(contextData + 3) == DAT_00e2b1a4) // offset +0xC
    {
        // Copy quaternion part (first 4 floats) from input to output
        outputTransform[0] = inputTransform[0];
        outputTransform[1] = inputTransform[1];
        outputTransform[2] = inputTransform[2];
        outputTransform[3] = inputTransform[3];
    }
    else
    {
        FUN_0056cba0(); // error handler
    }

    // Save original w of translation part (output[7])
    float originalTranslationW = outputTransform[7];

    // Add translation from input and context
    outputTransform[4] = inputTransform[4] + contextData[4]; // +0x10
    outputTransform[5] = inputTransform[5] + contextData[5]; // +0x14
    outputTransform[6] = inputTransform[6] + contextData[6]; // +0x18
    outputTransform[7] = inputTransform[7] + contextData[7]; // +0x1c (but then overwritten)
    // The above line is overridden by the next, so the addition to w is undone.
    outputTransform[7] = originalTranslationW; // preserve original w
}