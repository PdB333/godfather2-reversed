// FUNC_NAME: Entity::setFieldAt50
void __thiscall Entity::setFieldAt50(Entity *this, int value) {
    *(int *)((uintptr_t)this + 0x50) = value; // +0x50 Set field at offset 0x50
}