// FUNC_NAME: lineSegmentAABBIntersect
// Function address: 0x0084cd10
// Role: Checks intersection between a line segment (defined by two points) and an axis-aligned bounding box.
// Returns 1.0f if intersection occurs, 0.0f otherwise.

float lineSegmentAABBIntersect(const float* segmentStart, const float* segmentEnd,
                                const float* aabbMin, const float* aabbMax)
{
    // Direction vector from start to end
    float dx = segmentEnd[0] - segmentStart[0];
    float dy = segmentEnd[1] - segmentStart[1];
    float dz = segmentEnd[2] - segmentStart[2];

    // --- Test x-axis near plane (minX) ---
    if (dx != 0.0f) {
        // Compute t such that P = start + t*direction lies on x = aabbMin[0] plane.
        // Note: origin.x - aabbMin[0] instead of aabbMin[0] - origin.x (as in standard slab method).
        float t = (segmentStart[0] - aabbMin[0]) / dx;
        if (t >= 0.0f && t <= 1.0f) {
            float y = segmentStart[1] + dy * t;
            float z = segmentStart[2] + dz * t;
            if (y >= aabbMin[1] && y <= aabbMax[1] &&
                z >= aabbMin[2] && z <= aabbMax[2]) {
                return 1.0f;
            }
        }
    }

    // --- Test x-axis far plane (maxX) ---
    if (dx != 0.0f) {
        float t = (segmentStart[0] - aabbMax[0]) / dx;
        if (t >= 0.0f && t <= 1.0f) {
            float y = segmentStart[1] + dy * t;
            float z = segmentStart[2] + dz * t;
            if (y >= aabbMin[1] && y <= aabbMax[1] &&
                z >= aabbMin[2] && z <= aabbMax[2]) {
                return 1.0f;
            }
        }
    }

    // --- Test y-axis near plane (minY) ---
    if (dy != 0.0f) {
        float t = (segmentStart[1] - aabbMin[1]) / dy;
        if (t >= 0.0f && t <= 1.0f) {
            float x = segmentStart[0] + dx * t;
            float z = segmentStart[2] + dz * t;
            if (x >= aabbMin[0] && x <= aabbMax[0] &&
                z >= aabbMin[2] && z <= aabbMax[2]) {
                return 1.0f;
            }
        }
    }

    // --- Test y-axis far plane (maxY) ---
    if (dy != 0.0f) {
        float t = (segmentStart[1] - aabbMax[1]) / dy;
        if (t >= 0.0f && t <= 1.0f) {
            float x = segmentStart[0] + dx * t;
            float z = segmentStart[2] + dz * t;
            if (x >= aabbMin[0] && x <= aabbMax[0] &&
                z >= aabbMin[2] && z <= aabbMax[2]) {
                return 1.0f;
            }
        }
    }

    // --- Test z-axis near plane (minZ) ---
    if (dz != 0.0f) {
        float t = (segmentStart[2] - aabbMin[2]) / dz;
        if (t >= 0.0f && t <= 1.0f) {
            float x = segmentStart[0] + dx * t;
            float y = segmentStart[1] + dy * t;
            if (x >= aabbMin[0] && x <= aabbMax[0] &&
                y >= aabbMin[1] && y <= aabbMax[1]) {
                return 1.0f;
            }
        }
    }

    // --- Test z-axis far plane (maxZ) ---
    if (dz != 0.0f) {
        float t = (segmentStart[2] - aabbMax[2]) / dz;
        if (t >= 0.0f && t <= 1.0f) {
            float x = segmentStart[0] + dx * t;
            float y = segmentStart[1] + dy * t;
            if (x >= aabbMin[0] && x <= aabbMax[0] &&
                y >= aabbMin[1] && y <= aabbMax[1]) {
                return 1.0f;
            }
        }
    }

    // No intersection – return 0.0f (the original code generates a float with bit pattern 0x3F800000?).
    return 0.0f;
}