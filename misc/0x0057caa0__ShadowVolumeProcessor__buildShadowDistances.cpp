// FUNC_NAME: ShadowVolumeProcessor::buildShadowDistances
#include <cmath>

// Reconstructed from address 0x0057caa0
// This function computes shadow depth values for either single points (2D shadow) or capsules (two points).
// The input data array (pData) contains blocks of 8 floats (flag==0) or 16 floats (flag!=0) per element.
// The number of elements is assumed to be stored in the class member m_numElements (passed via EAX in original).
// Global constants:
//   kMaxRangeSq (DAT_00e2b1a4) – squared maximum shadow range
//   kShadowDistOffset (DAT_00e44564) – offset to flip signed distance

void __thiscall ShadowVolumeProcessor::buildShadowDistances(float* pData, int numElements, char flag)
{
    // Constants from global data
    float kMaxRangeSq = *reinterpret_cast<float*>(0x00e2b1a4);
    float kShadowDistOffset = *reinterpret_cast<float*>(0x00e44564);

    if (flag == '\0')
    {
        // Single point mode – each element is 8 floats (3 position, 1 flag, 4 padding)
        float* pEnd = pData + numElements * 8;
        for (float* pCur = pData; pCur != pEnd; pCur += 8)
        {
            float x = pCur[0];
            float y = pCur[1];
            float z = pCur[2];
            float distSq = x*x + y*y + z*z;
            float dist = 0.0f;
            if (kMaxRangeSq > distSq)
            {
                dist = std::sqrt(kMaxRangeSq - distSq);
            }
            // If the flag (stored at index 3) is non‑zero, invert the distance
            if (pCur[3] != 0.0f)
            {
                dist = kShadowDistOffset - dist;
            }
            pCur[3] = dist;
        }
    }
    else
    {
        // Capsule (two‑point) mode – each element is 16 floats (two ×(3 pos,1 flag), 8 padding)
        float* pEnd = pData + numElements * 16;
        for (float* pCur = pData; pCur != pEnd; pCur += 16)
        {
            // First point
            float x1 = pCur[0];
            float y1 = pCur[1];
            float z1 = pCur[2];
            float distSq1 = x1*x1 + y1*y1 + z1*z1;
            float dist1 = 0.0f;
            if (kMaxRangeSq > distSq1)
            {
                dist1 = std::sqrt(kMaxRangeSq - distSq1);
            }
            if (pCur[3] != 0.0f)
            {
                dist1 = kShadowDistOffset - dist1;
            }
            pCur[3] = dist1;

            // Second point (starts at index 4)
            float x2 = pCur[4];
            float y2 = pCur[5];
            float z2 = pCur[6];
            float distSq2 = x2*x2 + y2*y2 + z2*z2;
            float dist2 = 0.0f;
            if (kMaxRangeSq > distSq2)
            {
                dist2 = std::sqrt(kMaxRangeSq - distSq2);
            }
            if (pCur[7] != 0.0f)
            {
                dist2 = kShadowDistOffset - dist2;
            }
            pCur[7] = dist2;
        }
    }
}