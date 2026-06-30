// FUNC_NAME: SceneObject::getSquaredDistanceToPoint
// Function at 0x004702b0: Computes squared Euclidean distance between this object's position (stored at offsets +0x100, +0x104, +0x108) and a given 3D point.
// Used extensively for proximity checks (e.g., AI perception, collision, targeting).
float SceneObject::getSquaredDistanceToPoint(const float* point) const
{
    // Object position fields (likely part of a Transform or SceneNode)
    // +0x100: float positionX
    // +0x104: float positionY
    // +0x108: float positionZ
    float dx = point[0] - *(float*)((uintptr_t)this + 0x100);
    float dy = point[1] - *(float*)((uintptr_t)this + 0x104);
    float dz = point[2] - *(float*)((uintptr_t)this + 0x108);
    
    // Squared distance (avoids sqrt for performance)
    return dx * dx + dy * dy + dz * dz;
}