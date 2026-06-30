// FUNC_NAME: Vector4::project (static)
// Function at 0x0056dd50: 3D vector projection onto another vector, preserving w component.
// Uses bitwise absolute value trick to avoid division by zero on near-zero direction vectors.

static const float kEpsilon = 0.00000011920928955078125f;  // DAT_00e44598 (small positive float)
static const uint32_t kAbsMask   = 0x7FFFFFFF;               // DAT_00e44680 (clear sign bit)

// Projects 'vectorToProject' onto 'direction', storing result in 'result'.
// Returns 1 if successful (direction length > epsilon), 0 otherwise.
// The w component of 'result' is preserved from its original value.
int __thiscall Vector4::project(const Vector4& direction, const Vector4& vectorToProject, Vector4& result)
{
    float dx = direction.x;
    float dy = direction.y;
    float dz = direction.z;
    float squaredLength = dx*dx + dy*dy + dz*dz;

    // Check if squared length is > epsilon by taking absolute value as float
    float absSqrLen = (float)((uint32_t)squaredLength & kAbsMask);
    if (kEpsilon < absSqrLen)
    {
        float savedW = result.w;
        float dot = vectorToProject.x*dx + vectorToProject.y*dy + vectorToProject.z*dz;
        float scalar = dot / squaredLength;

        result.x = scalar * dx;
        result.y = scalar * dy;
        result.z = scalar * dz;
        result.w = savedW;  // Preserve original w
        return 1;
    }
    else
    {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
        // result.w unchanged? Not written, so left as-is.
        return 0;
    }
}