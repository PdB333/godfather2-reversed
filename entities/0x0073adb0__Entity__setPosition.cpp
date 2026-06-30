// FUNC_NAME: Entity::setPosition
void __thiscall Entity::setPosition(double x, double y, double z) {
    // Offsets: position vector (double precision) at +0x90, +0x98, +0xA0
    *(double*)((char*)this + 0x90) = x; // position.x
    *(double*)((char*)this + 0x98) = y; // position.y
    *(double*)((char*)this + 0xA0) = z; // position.z
    return;
}