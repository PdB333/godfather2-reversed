// FUNC_NAME: Entity::isFlagBit0
uint Entity::isFlagBit0() {
    return *(uint*)((char*)this + 0x2d8) & 1;
}