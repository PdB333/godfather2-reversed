// FUNC_NAME: Segment::closestPointOnSegment
// Function at 0x005fd8d0: Computes the closest point on a line segment defined by this->start and endPoint to queryPoint.
// Output is written to outResult if not null.
// Uses global constants: g_closestSegmentEpsilonSq (DAT_00e2b05c) and g_segmentMaxT (DAT_00e2b1a4).
void __thiscall Segment::closestPointOnSegment(const float* endPoint, const float* queryPoint, float* outResult)
{
    // this points to the segment's start point (three floats at offset 0, 4, 8)
    float startX = this[0];
    float startY = this[1];
    float startZ = this[2];

    float dx = endPoint[0] - startX;
    float dy = endPoint[1] - startY;
    float dz = endPoint[2] - startZ;

    float sqLen = dx*dx + dy*dy + dz*dz;

    // If the segment is long enough to avoid numerical issues, compute projection
    if (g_closestSegmentEpsilonSq < sqLen)
    {
        float px = queryPoint[0] - startX;
        float py = queryPoint[1] - startY;
        float pz = queryPoint[2] - startZ;

        // Project queryPoint onto the infinite line of the segment, then clamp to [0, maxT]
        float t = (px*dx + py*dy + pz*dz) / sqLen;
        if (t < 0.0f)
        {
            t = 0.0f;
        }
        else if (g_segmentMaxT < t)
        {
            t = g_segmentMaxT;
        }

        // Interpolate between start and end using clamped t
        float oneMinusT = g_segmentMaxT - t; // note: using maxT as the segment length? But t is already relative to [0, maxT]
        // Actually the original code used: fVar5 = DAT_00e2b1a4 - fVar4; and then lerp: local_c = fVar5 * startX + endPoint[0] * fVar4;
        // That implies the segment is parameterized such that the endpoint corresponds to t = maxT, not t = 1.0.
        // So we treat the segment as having length maxT in parameter space.
        float lerpX = oneMinusT * startX + t * endPoint[0];
        float lerpY = oneMinusT * startY + t * endPoint[1];
        float lerpZ = oneMinusT * startZ + t * endPoint[2];

        // Set the internal pointer to the local result for output
        this = &lerpX; // Note: This reassignment is only for the subsequent output condition
    }

    // If output pointer is provided, write the result (which may be the local or the original start if segment is too short)
    if (outResult != nullptr)
    {
        outResult[0] = this[0];
        outResult[1] = this[1];
        outResult[2] = this[2];
    }
}