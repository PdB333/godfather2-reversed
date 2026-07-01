// FUNC_NAME: pointSegmentDistanceSquared
// Function address: 0x0084ca90
// Computes the squared distance from a 2D point to a line segment.
// Optionally clamps the projection parameter to [0, 1] if doClamp is true.
// If outPoint is non-null, writes the closest point on the segment to it.
// If the segment endpoints are identical, uses the start point as the closest point.

float pointSegmentDistanceSquared(const float *point, const float *segmentStart, const float *segmentEnd, float *outPoint, bool doClamp) {
    float dx = segmentEnd[0] - segmentStart[0];  // +0x00 offset
    float dy = segmentEnd[1] - segmentStart[1];  // +0x04 offset

    if (dx != 0.0f || dy != 0.0f) {
        float t = ( (point[1] - segmentStart[1]) * dy + (point[0] - segmentStart[0]) * dx ) / (dx * dx + dy * dy);
        if (doClamp) {
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > 1.0f) {  // _DAT_00d5780c is 1.0f
                t = 1.0f;
            }
        }
        float closestX = (1.0f - t) * segmentStart[0] + t * segmentEnd[0];
        float closestY = (1.0f - t) * segmentStart[1] + t * segmentEnd[1];
        if (outPoint != nullptr) {
            outPoint[0] = closestX;
            outPoint[1] = closestY;
        }
        float diffX = point[0] - closestX;
        float diffY = point[1] - closestY;
        return diffX * diffX + diffY * diffY;
    } else {
        // Degenerate segment: use start point
        if (outPoint != nullptr) {
            outPoint[0] = segmentStart[0];
            outPoint[1] = segmentStart[1];
        }
        float diffX = point[0] - segmentStart[0];
        float diffY = point[1] - segmentStart[1];
        return diffX * diffX + diffY * diffY;
    }
}