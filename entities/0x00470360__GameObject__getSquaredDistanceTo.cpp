// FUNC_NAME: GameObject::getSquaredDistanceTo
// Computes squared Euclidean distance between this object's position (offset +0x100) and another's.
// Offsets: position.x at +0x100, position.y at +0x104, position.z at +0x108
float __thiscall GameObject::getSquaredDistanceTo(GameObject* other) const {
    // Assume Vector3 layout: { float x, y, z; } at offset 0x100
    const Vector3& thisPos = *(Vector3*)((uint8_t*)this + 0x100);
    const Vector3& otherPos = *(Vector3*)((uint8_t*)other + 0x100);
    float dx = otherPos.x - thisPos.x;
    float dy = otherPos.y - thisPos.y;
    // Use extended precision for z difference (matches float10 subtraction)
    double dz = (double)otherPos.z - (double)thisPos.z;
    return (float)((double)(dx*dx + dy*dy) + dz*dz);
}