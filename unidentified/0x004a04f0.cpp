// FUN_004a04f0: CollisionSystem::closestPointOnInfiniteLineWithRadius
// Computes the closest point on an infinite line (defined by direction vector param_2) to a point param_1,
// with a radius-threshold parameter param_5. Outputs the closest point in param_3 and a distance measure in param_4.
// Uses global constants: kRadiusBase (DAT_00e2b1a4), kEpsilon (DAT_00e44598), kAbsMask (DAT_00e44680), kThreshold (DAT_00e44564), kFallbackDist (DAT_00e2afac)

void __stdcall closestPointOnInfiniteLineWithRadius(float* point, float* lineDir, float* outPoint, float* outDistance, float radius)
{
    // Global constants (reinterpreted from memory)
    static const float kRadiusBase = *reinterpret_cast<const float*>(0x00e2b1a4);
    static const float kEpsilon = *reinterpret_cast<const float*>(0x00e44598);
    static const uint32_t kAbsMask = *reinterpret_cast<const uint32_t*>(0x00e44680); // typically 0x7FFFFFFF
    static const float kThreshold = *reinterpret_cast<const float*>(0x00e44564);
    static const float kFallbackDist = *reinterpret_cast<const float*>(0x00e2afac);

    float px = point[0];
    float py = point[1];
    float pz = point[2];

    // Dot product of point with lineDir (projects point onto line)
    float dot = lineDir[0] * px + lineDir[1] * py + lineDir[2] * pz;

    // Radius squared threshold
    float radiusSq = (kRadiusBase - radius) * (kRadiusBase - radius);

    // Check if projection is inside the sphere and point is not close to lineDir
    uint32_t diffX = *(uint32_t*)(&px) - *(uint32_t*)(&lineDir[0]) & kAbsMask;
    uint32_t diffY = *(uint32_t*)(&py) - *(uint32_t*)(&lineDir[1]) & kAbsMask;
    uint32_t diffZ = *(uint32_t*)(&pz) - *(uint32_t*)(&lineDir[2]) & kAbsMask;

    if (dot < radiusSq &&
        (kEpsilon < *(float*)&diffX || kEpsilon < *(float*)&diffY || kEpsilon < *(float*)&diffZ))
    {
        if (kThreshold - radiusSq < dot)
        {
            // Point is far from line origin along direction: use cross product for perpendicular component
            outPoint[0] = py * lineDir[2] - pz * lineDir[1];
            outPoint[1] = pz * lineDir[0] - px * lineDir[2];
            outPoint[2] = px * lineDir[1] - py * lineDir[0];
            // Normalize the perpendicular vector
            normalizeVector(outPoint, outPoint);
            // Square root call (unused result but side effect?)
            sqrtFunction(); // likely math function, discarding result
            *outDistance = dot; // return dot product as distance
            return;
        }
        else
        {
            // Check if point is degenerate (all components nearly equal)
            uint32_t diffPX_PY = *(uint32_t*)(&py) - *(uint32_t*)(&px) & kAbsMask;
            uint32_t diffPY_PZ = *(uint32_t*)(&pz) - *(uint32_t*)(&py) & kAbsMask;
            uint32_t diffPZ_PX = *(uint32_t*)(&px) - *(uint32_t*)(&pz) & kAbsMask;
            if (*(float*)&diffPX_PY <= kEpsilon && *(float*)&diffPY_PZ <= kEpsilon && *(float*)&diffPZ_PX <= kEpsilon)
            {
                py = kThreshold - py; // adjust y component
            }
            // Compute a vector based on a weird cross-like product
            outPoint[0] = pz * pz - px * py;
            outPoint[1] = px * px - pz * py;
            outPoint[2] = py * py - px * pz;
            normalizeVector(outPoint, outPoint);
            *outDistance = kFallbackDist;
            return;
        }
    }

    // Default: copy point directly
    outPoint[0] = px;
    outPoint[1] = py;
    outPoint[2] = pz;
    *outDistance = 0.0f;
}