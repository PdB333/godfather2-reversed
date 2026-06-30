// FUNC_NAME: TransformNode::interpolateTransform

// Reconstructed from Ghidra at 0x00574760
// Interpolate a transform (rotation as quaternion, translation as vector)
// based on flags and blend factor, and apply to output and this object's transform.

struct TransformData {
    float matrix[4][4]; // 16 floats, but actually quaternion + translation?
    // Offsets 0x00-0x0F: rotation matrix or quaternion (4 floats for quat? but used as 4 undefined4 each row?)
    float translation[3]; // +0x10? Actually after matrix, translation at offsets 0x30? Need better understanding.
};

// Structure for interpolation control
struct InterpControl {
    TransformData* srcTransform; // +0x00
    int field_0x04; // some index or target transform pointer?
    float* blendTime; // +0x08 pointer to blend factor (float)
    ushort flags;    // +0x0C (low 2 bytes)
};

// Constants from data segment
extern undefined4 DAT_00e2b1a4;  // Likely 1.0f (identity quaternion w)
extern undefined4 DAT_00e2e780;  // Some constant, maybe another identity or pointer

void __thiscall TransformNode::interpolateTransform(TransformNode* this, undefined4 param_1)
{
    float blendFactor;
    float* pBlendFactor;
    undefined4* srcMatrix;
    int blendTargetOffset;
    undefined4 local_30[4]; // 4x4 matrix? Actually 4 uint32s
    float translation[4];   // local_20, fStack_1c, fStack_18, uStack_14

    InterpControl* control = (InterpControl*)this; // this points to InterpControl structure? Actually in_EAX is this
    // Wait: this is in EAX according to usage. So reinterpret this as InterpControl
    // But then extraout_ECX after calls is the same this pointer? The code later writes to extraout_ECX + offsets.
    // So this object has InterpControl fields at the start, and later stores translation at +0x30.
    // This suggests the class has both the interpolation control data and the output transform.

    pBlendFactor = (float*)control->blendTime; // pfVar2
    if (pBlendFactor != (float*)0x0) {
        srcMatrix = (undefined4*)control->srcTransform; // puVar3
        // Initialize rotation part with identity? Actually DAT_00e2b1a4 is probably 1.0f for quaternion w
        local_30[0] = 0;
        local_30[1] = 0;
        local_30[2] = 0;
        local_30[3] = DAT_00e2b1a4; // Set w to 1
        // Initialize translation with zeros
        translation[0] = 0.0f;
        translation[1] = 0.0f;
        translation[2] = 0.0f;
        translation[3] = DAT_00e2b1a4; // w component of translation? Possibly unused.

        // Check bit 4 of flags (0x4) - indicates interpolation for rotation (quaternion)
        if ((control->flags & 0x4) == 0) {
            // No interpolation: copy source matrix directly
            local_30[0] = srcMatrix[0];
            local_30[1] = srcMatrix[1];
            local_30[2] = srcMatrix[2];
            local_30[3] = srcMatrix[3];
        }
        else {
            // Interpolate rotation using quaternion slerp or similar
            // FUN_0056cc80 likely does slerp between two quaternions
            // Parameters: blendFactor, srcMatrix (current), control->field_0x04 (target), output local_30, DAT_00e2e780 (some const)
            FUN_0056cc80(*pBlendFactor, srcMatrix, control->field_0x04, &local_30, DAT_00e2e780);
        }

        // Check bit 8 of flags (0x8) - indicates interpolation for translation
        if ((control->flags & 0x8) == 0) {
            // No interpolation: copy source translation (srcMatrix + 4 = translation vector)
            translation[0] = (float)srcMatrix[4];
            translation[1] = (float)srcMatrix[5];
            translation[2] = (float)srcMatrix[6];
            translation[3] = (undefined4)srcMatrix[7]; // not cast?
        }
        else {
            // Interpolate translation linearly
            blendFactor = *pBlendFactor;
            // srcMatrix[4..6] are translation, target is at control->field_0x04 + 0x10
            translation[0] = (*(float*)(control->field_0x04 + 0x10) - (float)srcMatrix[4]) * blendFactor + (float)srcMatrix[4];
            translation[1] = (*(float*)(control->field_0x04 + 0x14) - (float)srcMatrix[5]) * blendFactor + (float)srcMatrix[5];
            translation[2] = (*(float*)(control->field_0x04 + 0x18) - (float)srcMatrix[6]) * blendFactor + (float)srcMatrix[6];
        }

        // Apply the blended transform to the output (param_1) via FUN_0056cef0
        // FUN_0056cef0 likely combines rotation and translation into a 4x4 matrix
        FUN_0056cef0(&local_30, param_1);

        // Store the resulting translation into this object's transform at offsets 0x30-0x3c
        // This suggests this object has a transform structure at offsets 0x30+
        float* thisTransform = (float*)((char*)this + 0x30);
        thisTransform[0] = translation[0];   // +0x30: x
        thisTransform[1] = translation[1];   // +0x34: y
        thisTransform[2] = translation[2];   // +0x38: z
        *((undefined4*)(thisTransform + 3)) = translation[3]; // +0x3c: w (set to DAT_00e2b1a4 later)
        // Overwrite w with identity constant (likely 1.0f) - possibly bug but as decompiled
        *((undefined4*)(thisTransform + 3)) = DAT_00e2b1a4;

        // Call cleanup or finalize function
        FUN_00417560();
    }
    return;
}