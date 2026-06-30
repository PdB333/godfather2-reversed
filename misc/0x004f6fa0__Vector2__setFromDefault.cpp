// FUNC_NAME: Vector2::setFromDefault
// Address: 0x004f6fa0
// Role: Initializes a 2-float vector by first zeroing it, then copying from a static default value retrieved via a helper function.
//       The helper function (0x004f7050) takes a 12-byte scratch buffer and returns a pointer to the default 2-float pair.

struct Vector2 {
    float x; // +0x00
    float y; // +0x04
};

void Vector2::setFromDefault()
{
    // Clear both components (safety initialization, later overwritten).
    this->x = 0.0f;
    this->y = 0.0f;

    // Temporary buffer (12 bytes) used by the helper to compute/provide default values.
    char tempBuffer[12];

    // Get pointer to a default Vector2 from the helper function.
    // Helper returns a pointer to two floats (cast from undefined4*).
    Vector2* pDefault = reinterpret_cast<Vector2*>(getDefaultVector2(tempBuffer));

    // Copy the default components into this vector.
    this->x = pDefault->x;
    this->y = pDefault->y;
}