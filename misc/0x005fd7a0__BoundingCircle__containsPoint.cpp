// FUNC_NAME: BoundingCircle::containsPoint
// Function address: 0x005fd7a0
// Checks if a 2D point (param_2) is within the circle defined by this instance.
// Object fields: +0x10 = centerX, +0x14 = centerY, +0x18 = radius
bool __thiscall BoundingCircle::containsPoint(float *point) {
    float dx = point[0] - *(float *)(this + 0x10);
    float dy = point[1] - *(float *)(this + 0x14);
    float radius = *(float *)(this + 0x18);
    float distSq = dx * dx + dy * dy;
    return distSq < radius * radius;
}