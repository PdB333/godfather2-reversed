// FUNC_NAME: Entity::setPositionWithThreshold
void __thiscall Entity::setPositionWithThreshold(float *newPos) {
    char isActive = FUN_00481660(); // likely Entity::isActive() or similar
    if (isActive) {
        float dx = *(float *)(this + 0x8F0) - newPos[0]; // position.x
        float dy = *(float *)(this + 0x8F4) - newPos[1]; // position.y
        float dz = *(float *)(this + 0x8F8) - newPos[2]; // position.z
        float distSq = dx*dx + dy*dy + dz*dz;
        if (DAT_00d5efb8 < distSq) { // global squared movement threshold
            // vtable index 10 (0x28/4) -> likely OnPositionChanged
            (**(code **)(*(int *)(this + 0x58) + 0x28))(0x40);
        }
    }
    // Copy x and y as 8-byte aligned pair, then z separately
    *(undefined8 *)(this + 0x8F0) = *(undefined8 *)newPos; // x, y
    *(float *)(this + 0x8F8) = newPos[2]; // z
}