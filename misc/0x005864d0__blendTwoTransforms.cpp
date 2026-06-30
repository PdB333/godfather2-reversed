// FUNC_NAME: blendTwoTransforms
// Address: 0x005864d0
// Description: Blends two animation transform data sets (type 0 = static, type 2 = animated) into an output.
// Handles copying, scaling, and likely quaternion interpolation via FUN_00582b70.

extern float DAT_00e2b1a4;  // Global scaling constant, likely 1.0f
extern void FUN_00582b70(); // Presumed quaternion slerp helper

// Structure for each transform input/output:
// +0x00: char type (0 = static, 2 = animated)
// +0x04: float* translation (pointer to 4 floats: x,y,z,w)
// +0x08: float* rotation   (pointer to 4 floats: quaternion x,y,z,w)
// Note: The translation pointer actually points to 8 floats (translation + rotation?),
// and rotation pointer points to 4 floats (scale?).
// See code for details.

void blendTwoTransforms(undefined4* outData, undefined4* source2, undefined4* source3) {
    char type2 = *(char*)(*source2);        // +0x00 of source2
    char type3 = *(char*)(*source3);        // +0x00 of source3
    char* outType = (char*)(*outData);       // +0x00 of output

    if (type2 != 2) {
        if (type3 == 2) {
            // Source2 static, source3 animated: copy from source3
            *outType = 2;

            // Copy 8 floats from source3 translation pointer to output translation pointer
            // (assumes translation+quaternion combined)
            float* src3Pos = (float*)source3[1];  // +0x04
            float* dstPos = (float*)outData[1];   // +0x04
            for (int i = 0; i < 8; ++i) {
                dstPos[i] = src3Pos[i];
            }

            // Copy 4 floats from source3 rotation pointer to output rotation pointer
            // (likely scale or orientation)
            float* src3Rot = (float*)source3[2];  // +0x08
            float* dstRot = (float*)outData[2];   // +0x08
            dstRot[0] = src3Rot[0];
            dstRot[1] = src3Rot[1];
            dstRot[2] = src3Rot[2];
            dstRot[3] = src3Rot[3];
        } else {
            // Both static: output type 0
            *outType = 0;
        }
    } else {
        // Source2 is animated
        *outType = 2;
        if (type3 == 2) {
            // Both animated: perform blend (quaternion slerp and scale adjustment)
            FUN_00582b70();  // Assumed to blend quaternion and possibly copy translation/rotation

            float constant = DAT_00e2b1a4;
            float* src3Scale = (float*)source3[2];  // +0x08 of source3 (scale source)
            float* src2Scale = (float*)source2[2];  // +0x08 of source2 (scale target)
            float* outScale  = (float*)outData[2];  // +0x08 of output

            // Normalize scale: source2 scale adjusted by source3 scale inverted
            float invX = constant / src3Scale[0];
            float invY = constant / src3Scale[1];
            float invZ = constant / src3Scale[2];
            outScale[0] = src2Scale[0] * invX;
            outScale[1] = src2Scale[1] * invY;
            outScale[2] = src2Scale[2] * invZ;
            // W component: scaled then overwritten with constant
            float wScaled = src2Scale[3] * constant;
            outScale[3] = wScaled;
            outScale[3] = constant;  // Final w = constant (likely 1.0 or 0.0)
        } else {
            // Source3 static: copy from source2
            float* src2Pos = (float*)source2[1];  // +0x04
            float* dstPos = (float*)outData[1];   // +0x04
            for (int i = 0; i < 8; ++i) {
                dstPos[i] = src2Pos[i];
            }

            float* src2Rot = (float*)source2[2];  // +0x08
            float* dstRot = (float*)outData[2];   // +0x08
            dstRot[0] = src2Rot[0];
            dstRot[1] = src2Rot[1];
            dstRot[2] = src2Rot[2];
            dstRot[3] = src2Rot[3];
        }
    }
}