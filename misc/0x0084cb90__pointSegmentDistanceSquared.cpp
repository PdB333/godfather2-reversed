// FUNC_NAME: pointSegmentDistanceSquared
float pointSegmentDistanceSquared(const float* point, const float* segmentStart, const float* segmentEnd, float* outClosestPoint, bool clampToSegment)
{
    float dx = segmentEnd[0] - segmentStart[0];
    float dy = segmentEnd[1] - segmentStart[1];
    float dz = segmentEnd[2] - segmentStart[2];

    float segLenSq = dx*dx + dy*dy + dz*dz;

    // _DAT_00d577a0: small epsilon to avoid division by zero (approx 1e-10)
    const float kEpsilon = 1e-10f;  // guessed value, original: _DAT_00d577a0

    if (segLenSq > kEpsilon)
    {
        // Project point onto the line (parameter t)
        float t = ((point[0] - segmentStart[0]) * dx +
                   (point[1] - segmentStart[1]) * dy +
                   (point[2] - segmentStart[2]) * dz) / segLenSq;

        if (clampToSegment)
        {
            // Clamp t to [0,1] for segment
            if (t < 0.0f) t = 0.0f;
            // _DAT_00d5780c: likely 1.0f
            const float kOne = 1.0f;  // original: _DAT_00d5780c
            if (t > kOne) t = kOne;
        }

        // Compute closest point on line/segment via linear interpolation
        float invT = 1.0f - t;  // _DAT_00d5780c - t, note original had _DAT_00d5780c (1.0)
        float closestX = invT * segmentStart[0] + t * segmentEnd[0];
        float closestY = invT * segmentStart[1] + t * segmentEnd[1];
        float closestZ = invT * segmentStart[2] + t * segmentEnd[2];

        // If output pointer provided, store the closest point
        if (outClosestPoint)
        {
            outClosestPoint[0] = closestX;
            outClosestPoint[1] = closestY;
            outClosestPoint[2] = closestZ;
        }

        // Use the computed closest point for distance calculation
        segmentStart = &closestX;  // point to local array (note: original used same pointer trick)
    }
    else
    {
        // Segment is degenerate; use segmentStart as closest point
        if (outClosestPoint)
        {
            outClosestPoint[0] = segmentStart[0];
            outClosestPoint[1] = segmentStart[1];
            outClosestPoint[2] = segmentStart[2];
        }
    }

    // Return squared distance from point to closest point
    float ddx = point[0] - segmentStart[0];
    float ddy = point[1] - segmentStart[1];
    float ddz = point[2] - segmentStart[2];

    return ddx*ddx + ddy*ddy + ddz*ddz;
}