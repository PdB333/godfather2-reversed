// FUNC_NAME: Entity::setFlagMembers
void __thiscall Entity::setFlagMembers(Entity *this) {
    // Reads two 32-bit values at offsets +0x80 and +0x88 from this, then calls
    // a helper (likely SetFlag) with those values and a constant 1 (true).
    SetFlag(*(int *)((int)this + 0x80), *(int *)((int)this + 0x88), 1);
}