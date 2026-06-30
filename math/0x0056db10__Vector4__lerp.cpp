// FUNC_NAME: Vector4::lerp
// Address: 0x0056db10
// Role: Performs linear interpolation between two 4-component vectors (direction vectors, w forced to 0).
// Uses global constant at 0x00e2b1a4 (assumed 1.0f) for inverse factor calculation.
// Offsets: Vector4 members at +0x10 (x), +0x14 (y), +0x18 (z), +0x1c (w)

extern float g_oneFloat; // DAT_00e2b1a4 (likely 1.0f)

void __thiscall Vector4::lerp(const Vector4* v1, const Vector4* v2, float t) {
    float invT = g_oneFloat - t; // 1.0f - t
    float outX = invT * v1->x;   // +0x10
    float outY = invT * v1->y;   // +0x14
    float outZ = invT * v1->z;   // +0x18
    float outW = invT * v1->w;   // +0x1c

    this->x = t * v2->x + outX;  // +0x10
    this->y = t * v2->y + outY;  // +0x14
    this->z = t * v2->z + outZ;  // +0x18
    this->w = t * v2->w + outW;  // +0x1c
    this->w = 0.0f;              // Force w to 0 for directional vector
}