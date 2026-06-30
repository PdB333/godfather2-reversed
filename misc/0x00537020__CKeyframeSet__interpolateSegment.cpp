// FUNC_NAME: CKeyframeSet::interpolateSegment
// Address: 0x00537020
// Role: Evaluates a point along a keyframe curve given a normalized time parameter t.
//       The curve is defined by keyframes stored as float4 (x,y,z,w) where w is an index to the next keyframe.
//       The function computes an interpolated position using the x-difference as blend factor (unusual).
//       It also appears to call a random number generator and sets the output w to a global value.

void CKeyframeSet::interpolateSegment(short segmentCount, float t, float* pOut) // __thiscall
{
    float *pfVar1;
    float diffX;
    float diffY;
    float diffZ;
    float diffW;
    float factor;
    float y1, z1, w1;
    int segmentIndex;
    float *pKey1, *pKey2;
    int maxIndex;
    int numSegments = segmentCount; // param_1

    // Call to unknown function, possibly random number generator
    FUN_004e41b0();

    // Compute segment index based on t and segmentCount
    segmentIndex = (int)(t * (float)numSegments) + 1;
    if (segmentIndex < 1) {
        segmentIndex = 0;
    } else {
        // Use keyframe count from this+0x2 as max index (count of keys? minus 1?)
        maxIndex = *(short*)(this + 2) - 1; // +0x2: short keyframeCount
        if (maxIndex <= segmentIndex) {
            segmentIndex = maxIndex;
        }
    }

    // Keyframe array at this+0x8, stride 0x10 (4 floats)
    pKey1 = (float*)(segmentIndex * 0x10 + *(int*)(this + 8)); // +0x8: pointer to keyframe data
    y1 = pKey1[1];
    z1 = pKey1[2];
    // The fourth float is actually an index to the next keyframe (stored as short)
    pKey2 = (float*)(*(short*)(pKey1 + 3) * 0x10 + *(int*)(this + 8));

    float dX = pKey2[0] - pKey1[0];
    float dY = pKey2[1] - y1;
    float dZ = pKey2[2] - z1;
    float dW = pKey2[3] - pKey1[3];

    // Store difference vector to output
    pOut[0] = dX;
    pOut[1] = dY;
    pOut[2] = dZ;
    pOut[3] = dW;

    // Second call to unknown function
    FUN_004e41b0();

    // Read global value (maybe a random or constant)
    float globalW = DAT_00e2b1a4; // global float

    // Perform interpolation using the x-difference as blend factor (unusual)
    pOut[0] = pOut[0] * dX + pKey1[0]; // dX * dX + pKey1[0]
    pOut[1] = pOut[1] * dX + y1;
    pOut[2] = pOut[2] * dX + z1;
    pOut[3] = globalW; // override w with global value

    return;
}