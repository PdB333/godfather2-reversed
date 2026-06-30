// FUNC_NAME: AnimationManager::blendBoneTransforms
// Address: 0x0057ccc0
// Role: Interpolates bone transforms from a global animation blend data array based on flags.
// The function takes an output float array (8 floats per bone), a count of bones, a flag array,
// and a blend factor (0.0 to 1.0). For each bone with flag == 2, it reads two sets of 4 floats
// (likely quaternion or position components) from the global blend data and linearly interpolates
// them into the output. The global data is a static array (DAT_01223d60) containing pairs of
// 8-float blocks (16 floats per flagged bone entry).

void __thiscall AnimationManager::blendBoneTransforms(float* outBoneData, int boneCount, char* boneFlags, float blendFactor)
{
    float* endOut = outBoneData + boneCount * 8; // +0x00: end pointer for loop
    float* srcData = (float*)&DAT_01223d60;      // +0x04: global blend source data

    if (outBoneData != endOut) {
        do {
            if (*boneFlags == 0x02) {
                // Interpolate first 4 floats (e.g., position or quaternion part 1)
                float from0 = srcData[-8];
                float from1 = srcData[-7];
                float from2 = srcData[-6];
                float from3 = srcData[-5];
                float to0   = srcData[-4];
                float to1   = srcData[-3];
                float to2   = srcData[-2];
                float to3   = srcData[-1];

                outBoneData[0] = (to0 - from0) * blendFactor + from0;
                outBoneData[1] = (to1 - from1) * blendFactor + from1;
                outBoneData[2] = (to2 - from2) * blendFactor + from2;
                outBoneData[3] = (to3 - from3) * blendFactor + from3;

                // Interpolate second 4 floats (e.g., position or quaternion part 2)
                float from4 = srcData[0];
                float from5 = srcData[1];
                float from6 = srcData[2];
                float from7 = srcData[3];
                float to4   = srcData[4];
                float to5   = srcData[5];
                float to6   = srcData[6];
                float to7   = srcData[7];

                outBoneData[4] = (to4 - from4) * blendFactor + from4;
                outBoneData[5] = (to5 - from5) * blendFactor + from5;
                outBoneData[6] = (to6 - from6) * blendFactor + from6;
                outBoneData[7] = (to7 - from7) * blendFactor + from7;

                srcData += 16; // Advance to next blend pair (16 floats)
            }
            outBoneData += 8;  // Move to next bone output slot
            boneFlags++;       // Next flag byte
        } while (outBoneData != endOut);
    }
}