// FUNC_NAME: Transform::combineTransforms (or Transform::multiplyTransform)
// Function address: 0x00582ea0
// This function combines two transform objects (represented as 4x4 matrices?)
// It multiplies the translation components and sets a constant (likely 1.0) for the w component.
// param_1: pointer to source transform (input)
// param_2: pointer to destination transform (output)
// in_EAX: this pointer to a transform (likely the parent or base)

#include <cstdint>

class Transform {
public:
    // Offset +0x4: pointer to internal matrix data (likely a D3DXMATRIX or custom 4x4)
    // Layout of matrix data (4x4 float, column-major):
    // [0x00..0x0F]: rotation/scale part (3x3)
    // [0x10]: translation x
    // [0x14]: translation y
    // [0x18]: translation z
    // [0x1C]: w component (usually 1.0 for affine)
    float* getMatrixData() const { return *(float**)(this + 4); }

    void combineTransforms(Transform* other, Transform* result);
};

// Forward declaration of the matrix multiplication function (likely multiplies the rotation/scale parts)
void multiplyRotationScales(float* a, float* b, float* out); // Address 0x0056cba0

void __thiscall Transform::combineTransforms(Transform* other, Transform* result) {
    float* thisMat = getMatrixData();
    float* otherMat = other->getMatrixData();
    float* resultMat = result->getMatrixData();

    // Multiply the rotation/scale components (first 12 floats of 4x4 matrix, or the 3x3 part)
    multiplyRotationScales(thisMat, otherMat, resultMat); // Call at 0x0056cba0

    // Add translation components (position) from both transforms
    float tx1 = thisMat[4];   // offset 0x10 in bytes, index 4 in float array
    float ty1 = thisMat[5];   // offset 0x14
    float tz1 = thisMat[6];   // offset 0x18
    float tx2 = otherMat[4];
    float ty2 = otherMat[5];
    float tz2 = otherMat[6];

    resultMat[4] = thisMat[0] + otherMat[0]; // Wait, decompiled: *(float*)(iVar2+0x10) = *(float*)(iVar1+0x10) + *(float*)(iVar3+0x10);
    // Actually the decompiled code shows:
    // *(float *)(iVar2 + 0x10) = *(float *)(iVar1 + 0x10) + *(float *)(iVar3 + 0x10);
    // *(float *)(iVar2 + 0x14) = *(float *)(iVar1 + 0x14) + *(float *)(iVar3 + 0x14);
    // *(float *)(iVar2 + 0x18) = *(float *)(iVar1 + 0x18) + *(float *)(iVar3 + 0x18);
    // Then immediately after: *(undefined4 *)(iVar2 + 0x1c) = DAT_00e2b1a4;
    // So they read from iVar1 (source1) and iVar3 (this) and add to iVar2 (result).
    // But they also assign a constant to 0x1c. This is confusing.
    // Re-examine: In the code, iVar1 = *(int*)(param_1+4) -> source1 matrix data
    // iVar2 = *(int*)(param_2+4) -> result matrix data
    // iVar3 = *(int*)(in_EAX+4) -> this matrix data
    // Then they read from iVar1 and iVar3 and add into iVar2.
    // So the translation of result = translation of source1 + translation of this.
    // Then they set the w component (offset 0x1c) to a constant (likely 1.0f).
    // This suggests that the function computes a combined translation, not a full matrix multiply of translation.
    // But they also called multiplyRotationScales on the matrices. So the overall effect is:
    // result = this * source1 in terms of rotation/scale, and result.translation = this.translation + source1.translation.
    // That is a typical "combine" operation for affine transformations where rotation is multiplied and translation is added.
    // However the constant overwrite indicates the w component is set to 1.0 (for homogeneous coordinates).

    float constantW = *(float*)0x00e2b1a4; // likely 1.0f
    resultMat[7] = constantW; // offset 0x1c

    // Note: The ordering of addition: source1 translation + this translation.
    // In matrix multiplication of affine transforms, if result = M1 * M2, then translation = M1.translation + M1.rotation * M2.translation.
    // This code does simple addition, not rotation*translation. So it's likely a simplified combination where rotation parts are
    // separate and translation is just added. This could be for a "local" transform combination (e.g., child + parent offset).
    // Alternatively, the matrix multiplication function might already handle translation? Unclear.
    // For now, we'll implement as decompiled: add translation and set w.

    // Actually let's re-read the decompiled code carefully:
    // fVar4 = *(float *)(iVar1 + 0x14); // source1 y
    // fVar5 = *(float *)(iVar1 + 0x18); // source1 z
    // fVar6 = *(float *)(iVar1 + 0x1c); // source1 w
    // fVar7 = *(float *)(iVar3 + 0x14); // this y
    // fVar8 = *(float *)(iVar3 + 0x18); // this z
    // fVar9 = *(float *)(iVar3 + 0x1c); // this w
    // Then:
    // *(float *)(iVar2 + 0x10) = *(float *)(iVar1 + 0x10) + *(float *)(iVar3 + 0x10); // result.x = source1.x + this.x
    // *(float *)(iVar2 + 0x14) = fVar4 + fVar7; // result.y = source1.y + this.y
    // *(float *)(iVar2 + 0x18) = fVar5 + fVar8; // result.z = source1.z + this.z
    // *(float *)(iVar2 + 0x1c) = DAT_00e2b1a4; // result.w = constant
    // So they are using fVar6 and fVar9 (the w components) but not adding them? They are just read but not used in addition.
    // Actually they are read but then ignored. That's suspicious; maybe the decompiler optimized?
    // The constant assignment overwrites the sum of w components. So the w component is set to constant regardless of inputs.
    // This suggests this function is for combining two "translation vectors" (3D) and setting w to 1.
    // But the call to multiplyRotationScales suggests that the full matrix is involved.
    // Perhaps the matrix multiplication function (0x0056cba0) does the rotation/scale multiplication and also the translation part?
    // But then this function would only be adding translation? Let's assume the decompiled is correct: it adds only the translation
    // components and sets w to 1. The rotation/scale part is already handled by the call.

    // To match the decompiled exactly, we do the additions as shown.
    resultMat[4] = thisMat[4] + otherMat[4]; // x
    resultMat[5] = thisMat[5] + otherMat[5]; // y
    resultMat[6] = thisMat[6] + otherMat[6]; // z
    resultMat[7] = constantW; // w
}