// FUNC_NAME: Entity::getPosition
// Function at 0x0054be20: Retrieves the position vector from the transform object.
// The 'this' object has a pointer to a Transform at offset 0x14.
// The Transform stores position at offsets 0x10, 0x14, 0x18 (float x, y, z).
void __thiscall Entity::getPosition(Vector3& outPosition) {
    Transform* transform = *(Transform**)(this + 0x14); // Transform pointer at +0x14
    outPosition.x = *(float*)(transform + 0x10); // X coordinate
    outPosition.y = *(float*)(transform + 0x14); // Y coordinate
    outPosition.z = *(float*)(transform + 0x18); // Z coordinate
}