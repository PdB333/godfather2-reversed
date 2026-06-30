// FUNC_NAME: Entity::sphereIntersects
bool __thiscall Entity::sphereIntersects(float* position, float radius) {
    float dx = position[0] - *(float*)(this + 0x70); // +0x70: position.x
    float dy = position[1] - *(float*)(this + 0x74); // +0x74: position.y
    float dz = position[2] - *(float*)(this + 0x78); // +0x78: position.z
    float combinedRadius = *(float*)(this + 0x28) + radius; // +0x28: sphere radius
    float distSq = dx*dx + dy*dy + dz*dz;
    return distSq < combinedRadius * combinedRadius;
}