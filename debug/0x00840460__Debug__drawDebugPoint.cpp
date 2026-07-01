// FUNC_NAME: Debug::drawDebugPoint
// Function at 0x00840460: Draws a 3D debug point. Checks field at +0x170 (likely mDebugEnabled) but always calls internalDrawPoint anyway.
// param_2 points to three values (interpreted as float x,y,z or int color? Assume point for debug drawing).

struct Vector3 {
    float x;
    float y;
    float z;
};

class Debug {
public:
    // Offset +0x170: mDebugEnabled (int)
    int mDebugEnabled;

    // Static helper that actually renders the debug point
    static void internalDrawPoint(const Vector3* point);
};

void __thiscall Debug::drawDebugPoint(Debug* this, const Vector3* pPoint) {
    // Copy to local to avoid aliasing (as seen in decompiled copy of three words)
    Vector3 localPoint;
    localPoint.x = pPoint->x;
    localPoint.y = pPoint->y;
    localPoint.z = pPoint->z;

    // Original control flow: if enabled, call and return; else call (both paths same)
    if (this->mDebugEnabled != 0) {
        Debug::internalDrawPoint(&localPoint);
        return;
    }
    Debug::internalDrawPoint(&localPoint);
}