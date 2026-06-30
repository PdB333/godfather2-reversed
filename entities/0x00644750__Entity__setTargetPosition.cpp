// FUNC_NAME: Entity::setTargetPosition
// Address: 0x00644750
// Sets two fields at offsets 0x4AC and 0x4B0, likely a 2D target position (X, Y)
void __thiscall Entity::setTargetPosition(Entity *this, float x, float y) {
    *(float *)((unsigned char *)this + 0x4AC) = x; // +0x4AC: targetX
    *(float *)((unsigned char *)this + 0x4B0) = y; // +0x4B0: targetY
}