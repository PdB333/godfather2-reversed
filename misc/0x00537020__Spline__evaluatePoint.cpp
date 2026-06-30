// FUNC_NAME: Spline::evaluatePoint
#include <cstdint>

// Reconstructed from 0x00537020
// Evaluates a point on a piecewise linear curve defined by a list of 4D points.
// The class 'Spline' has:
//   +0x00: unknown (likely padding or other data)
//   +0x02: short m_numPointsMinusOne (number of points - 1)
//   +0x08: float* m_controlPoints (array of 4-float structs at stride 0x10)
// Each control point: {float x, y, z; union { float w; short nextIndex; } }
// The 4th component stored as float but used as a short index for the next point.

void Spline::evaluatePoint(short segmentCount, float t, float* outVec)
{
    // Clamp or compute initial index from t and segmentCount
    int index = static_cast<int>(t * static_cast<float>(segmentCount)) + 1;
    if (index < 1) {
        index = 0;
    } else {
        int maxIndex = *reinterpret_cast<short*>(reinterpret_cast<char*>(this) + 2) - 1;
        if (maxIndex <= index) {
            index = maxIndex;
        }
    }

    // Get control point at index
    float* p0 = reinterpret_cast<float*>(
        index * 0x10 + *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 8)
    );

    // Read next index stored as the 4th float (reinterpreted to short)
    short nextIdx = *reinterpret_cast<short*>(p0 + 3);
    float* p1 = reinterpret_cast<float*>(
        nextIdx * 0x10 + *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 8)
    );

    // Compute delta between the two points
    float dx = p1[0] - p0[0];
    float dy = p1[1] - p0[1];
    float dz = p1[2] - p0[2];
    float dw = p1[3] - p0[3];

    // Temporary store delta (will be overwritten)
    outVec[0] = dx;
    outVec[1] = dy;
    outVec[2] = dz;
    outVec[3] = dw;

    // Unknown helper function (may modify global state)
    FUN_004e41b0();

    // Global constant used as final W value
    float kDefaultW = DAT_00e2b1a4;

    // Interpolation using dx as factor?? (based on decompiled logic)
    // Note: This is not standard linear interpolation; the factor is the X component of the delta.
    outVec[0] = outVec[0] * dx + p0[0];
    outVec[1] = outVec[1] * dx + p0[1];
    outVec[2] = outVec[2] * dx + p0[2];
    outVec[3] = outVec[3] * dx + p0[3];

    // Override W with global constant
    outVec[3] = kDefaultW;
}