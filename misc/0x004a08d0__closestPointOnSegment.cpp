// FUNC_NAME: closestPointOnSegment
bool closestPointOnSegment(float* outPoint, const float* queryPoint, const float* segStart, const float* segEnd)
{
    // Segment direction vector
    float dx = segEnd[0] - segStart[0];
    float dy = segEnd[1] - segStart[1];
    float dz = segEnd[2] - segStart[2];

    // Squared length of segment
    float lenSq = dx * dx + dy * dy + dz * dz;

    bool insideSegment = true;  // Return value: true if projection falls on segment

    static const float kEpsilon = *reinterpret_cast<const float*>(0x00e44598); // Small threshold for degenerate segment
    if (lenSq <= kEpsilon)
    {
        // Degenerate segment – just use start point
        lenSq = 0.0f;
    }
    else
    {
        // Projection parameter t: dot(query - start, segment) / lenSq
        float t = ((queryPoint[1] - segStart[1]) * dy +
                   (queryPoint[0] - segStart[0]) * dx +
                   (queryPoint[2] - segStart[2]) * dz) / lenSq;

        // Clamp t to [0, 1]
        static const float kOne = *reinterpret_cast<const float*>(0x00e2b1a4); // 1.0f
        if (t < 0.0f || t > kOne)
        {
            t = (t < 0.0f) ? 0.0f : kOne;
            insideSegment = false;
        }

        // Compute closest point: segStart + t * segmentDirection
        lenSq = t; // reuse variable for t (lenSq not needed after this)
    }

    outPoint[0] = dx * lenSq + segStart[0];
    outPoint[1] = dy * lenSq + segStart[1];
    outPoint[2] = dz * lenSq + segStart[2];

    return insideSegment;
}