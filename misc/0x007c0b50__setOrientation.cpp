// FUNC_NAME: setOrientation
void __thiscall Entity::setOrientation(Entity* this, const double* orientation) {
    // Copy 4 8-byte values (e.g., quaternion of doubles) into object at offsets +0x74, +0x7c, +0x84, +0x8c
    *(double*)((uint8_t*)this + 0x74) = orientation[0];
    *(double*)((uint8_t*)this + 0x7c) = orientation[1];
    *(double*)((uint8_t*)this + 0x84) = orientation[2];
    *(double*)((uint8_t*)this + 0x8c) = orientation[3];
}