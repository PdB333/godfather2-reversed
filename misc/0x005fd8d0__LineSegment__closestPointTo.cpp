// FUNC_NAME: LineSegment::closestPointTo
// Address: 0x005fd8d0
// Computes the closest point on the line segment [this->start, end] to the given point.
// If the segment length squared is less than kEpsilonSq, the start point is used.
// The result is written to outResult if non-null.

struct Vector3 {
    float x, y, z;
};

// Global constants (likely defined elsewhere)
extern const float kEpsilonSq;   // DAT_00e2b05c
extern const float kMaxT;        // DAT_00e2b1a4 (usually 1.0f)

class LineSegment {
public:
    Vector3 start;  // +0x00

    void __thiscall closestPointTo(const Vector3& end, const Vector3& point, Vector3* outResult) {
        float dx = point.x - start.x;
        float dy = point.y - start.y;
        float dz = point.z - start.z;

        float ex = end.x - start.x;
        float ey = end.y - start.y;
        float ez = end.z - start.z;

        float lenSq = ex * ex + ey * ey + ez * ez;

        Vector3 result = start; // default to start

        if (lenSq > kEpsilonSq) {
            // Project point onto the line segment
            float t = (dx * ex + dy * ey + dz * ez) / lenSq;

            // Clamp t to [0, kMaxT]
            if (t < 0.0f) {
                t = 0.0f;
            } else if (t > kMaxT) {
                t = kMaxT;
            }

            // Interpolate between start and end
            float invT = kMaxT - t;
            result.x = invT * start.x + t * end.x;
            result.y = invT * start.y + t * end.y;
            result.z = invT * start.z + t * end.z;
        }

        if (outResult != nullptr) {
            *outResult = result;
        }
    }
};