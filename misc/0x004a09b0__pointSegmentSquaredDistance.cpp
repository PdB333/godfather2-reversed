// FUNC_NAME: pointSegmentSquaredDistance
float pointSegmentSquaredDistance(const float* point, const float* segmentStart, const float* segmentEnd, float* outParameter)
{
    // Compute vector from segment start to point
    float dx = point[0] - segmentStart[0];
    float dy = point[1] - segmentStart[1];
    float dz = point[2] - segmentStart[2];

    // Compute segment direction vector (start -> end)
    float dirX = segmentEnd[0] - segmentStart[0];
    float dirY = segmentEnd[1] - segmentStart[1];
    float dirZ = segmentEnd[2] - segmentStart[2];

    // Dot product of (point - start) and direction = t * len^2
    float dot = dx * dirX + dy * dirY + dz * dirZ;

    // Clamp parameter to [0,1] and compute closest point distance
    if (dot <= 0.0f)
    {
        *outParameter = 0.0f;
        // closest point = segmentStart, distance vector unchanged
    }
    else
    {
        float lenSq = dirX * dirX + dirY * dirY + dirZ * dirZ;
        if (lenSq <= dot) // projection beyond segmentEnd
        {
            *outParameter = 1.0f; // DAT_00e2b1a4 = 1.0
            // closest point = segmentEnd, adjust vector to point - end
            dx -= dirX;
            dy -= dirY;
            dz -= dirZ;
        }
        else // projection lies inside segment
        {
            float t = dot / lenSq;
            *outParameter = t;
            // vector becomes point - (start + t * direction)
            // Equivalent to: dx -= t * dirX, etc.
            // The code uses fVar2 = -t (since DAT_00e44564 = 0.0)
            dx -= t * dirX;
            dy -= t * dirY;
            dz -= t * dirZ;
        }
    }

    // Return squared distance to closest point on segment
    return dx * dx + dy * dy + dz * dz;
}