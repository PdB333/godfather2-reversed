// FUNC_NAME: Animation::blendBoneData
void __thiscall Animation::blendBoneData(int boneCount, const char* boneMask)
{
    // in_EAX (this) is a pointer to the output bone transforms array (8 floats per bone)
    float* outputBoneArray = reinterpret_cast<float*>(this); // Assumes 'this' points directly to the output buffer

    float* endOutput = outputBoneArray + boneCount * 8;   // advance by 8 floats per bone
    if (outputBoneArray == endOutput) {
        return; // no bones to process
    }

    // Global static array containing two sets of keyframe data per bone (16 floats per bone)
    // Layout: for each bone: [bone_i_keyframeA (8 floats)] [bone_i_keyframeB (8 floats)]
    float* keyframeData = reinterpret_cast<float*>(0x01223d60);

    // blendFactor is loaded into XMM2 register (e.g., from a class member or passed via SSE)
    float blendFactor = this->m_blendFactor;  // hypothetical member

    do {
        if (*boneMask == 0x02) {
            // Read first keyframe (A) for this bone: positions at keyframeData[-8..-1] (previous bone's data?)
            // More likely: keyframeData initially points to the start of the array for the first bone,
            // and the code uses negative indexing to reach the previous bone's data. We interpret as:
            // For bone i, the two keyframes are at keyframeData[0..7] and keyframeData[8..15].
            // But the decompiler shows negative indices because it advanced pointer before loop.
            // We'll simplify: assume keyframeData points to the first keyframe (A) of current bone.
            // The interpolation is: output = lerp(A, B, blendFactor)

            // First half: blend positions (indices 0-3) using keyframes A and B
            float ax = keyframeData[0]; // A[0]
            float ay = keyframeData[1]; // A[1]
            float az = keyframeData[2]; // A[2]
            float aw = keyframeData[3]; // A[3] (possibly quaternion w or other component)
            float bx = keyframeData[8]; // B[0]
            float by = keyframeData[9]; // B[1]
            float bz = keyframeData[10]; // B[2]
            float bw = keyframeData[11]; // B[3]

            outputBoneArray[0] = (bx - ax) * blendFactor + ax;
            outputBoneArray[1] = (by - ay) * blendFactor + ay;
            outputBoneArray[2] = (bz - az) * blendFactor + az;
            outputBoneArray[3] = (bw - aw) * blendFactor + aw;

            // Second half: blend another set of 4 values (indices 4-7)
            float ax2 = keyframeData[4]; // A[4]
            float ay2 = keyframeData[5]; // A[5]
            float az2 = keyframeData[6]; // A[6]
            float aw2 = keyframeData[7]; // A[7]
            float bx2 = keyframeData[12]; // B[4]
            float by2 = keyframeData[13]; // B[5]
            float bz2 = keyframeData[14]; // B[6]
            float bw2 = keyframeData[15]; // B[7]

            outputBoneArray[4] = (bx2 - ax2) * blendFactor + ax2;
            outputBoneArray[5] = (by2 - ay2) * blendFactor + ay2;
            outputBoneArray[6] = (bz2 - az2) * blendFactor + az2;
            outputBoneArray[7] = (bw2 - aw2) * blendFactor + aw2;

            // Advance to next bone's keyframe data (16 floats per bone)
            keyframeData += 16;
        } else {
            // Bone is not blended; advance pointer but output remains unchanged? 
            // Actually the loop always advances the output pointer, but only writes if mask == 0x02.
            // If not blended, output bone data is left as-is (pre-existing).
            keyframeData += 16; // still need to advance the keyframe reader?
        }

        // Move to next bone in output array (8 floats per bone)
        outputBoneArray += 8;
        boneMask++;
    } while (outputBoneArray != endOutput);
}