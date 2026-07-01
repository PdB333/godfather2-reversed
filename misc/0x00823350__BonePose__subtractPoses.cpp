// FUNC_NAME: BonePose::subtractPoses
// Address: 0x00823350
// Role: Performs per-element subtraction of three 4x4 element arrays (translations, rotations, scales)
// from sourceBonePose2 and sourceBonePose3, storing result in this.
// Each array: 4 elements of 4 floats each, stride 16 bytes.
// Offsets: +0x50 = array1 (e.g., translations), +0x90 = array2 (rotations), +0xd0 = array3 (scales)
// The loop processes 4 elements, stepping through each array by 16 bytes per iteration.

#include <cstddef>

// Forward declaration of helper called at function start (likely resets the destination arrays)
extern void resetPoseData(BonePose* dest);

class BonePose {
public:
    float mArray1[4][4]; // +0x50: first array (e.g., translation vectors)
    float mArray2[4][4]; // +0x90: second array (e.g., rotation quaternions)
    float mArray3[4][4]; // +0xd0: third array (e.g., scale vectors)

    BonePose* subtractPoses(const BonePose* sourceA, const BonePose* sourceB) {
        // Call helper to initialize/reset destination arrays (possibly zeroes or copies)
        resetPoseData(this);

        // Process all 4 elements across the three arrays
        for (int i = 0; i < 4; ++i) {
            // Subtract first array elements: this->mArray1[i] = sourceA->mArray1[i] - sourceB->mArray1[i]
            mArray1[i][0] = sourceA->mArray1[i][0] - sourceB->mArray1[i][0]; // x
            mArray1[i][1] = sourceA->mArray1[i][1] - sourceB->mArray1[i][1]; // y
            mArray1[i][2] = sourceA->mArray1[i][2] - sourceB->mArray1[i][2]; // z
            mArray1[i][3] = sourceA->mArray1[i][3] - sourceB->mArray1[i][3]; // w (if quaternion) or unused

            // Subtract second array elements: this->mArray2[i] = sourceA->mArray2[i] - sourceB->mArray2[i]
            mArray2[i][0] = sourceA->mArray2[i][0] - sourceB->mArray2[i][0];
            mArray2[i][1] = sourceA->mArray2[i][1] - sourceB->mArray2[i][1];
            mArray2[i][2] = sourceA->mArray2[i][2] - sourceB->mArray2[i][2];
            mArray2[i][3] = sourceA->mArray2[i][3] - sourceB->mArray2[i][3];

            // Subtract third array elements: this->mArray3[i] = sourceA->mArray3[i] - sourceB->mArray3[i]
            mArray3[i][0] = sourceA->mArray3[i][0] - sourceB->mArray3[i][0];
            mArray3[i][1] = sourceA->mArray3[i][1] - sourceB->mArray3[i][1];
            mArray3[i][2] = sourceA->mArray3[i][2] - sourceB->mArray3[i][2];
            mArray3[i][3] = sourceA->mArray3[i][3] - sourceB->mArray3[i][3];
        }

        return this;  // return pointer to destination
    }
};