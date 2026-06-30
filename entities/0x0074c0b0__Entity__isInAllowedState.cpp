// FUNC_NAME: Entity::isInAllowedState
bool __thiscall Entity::isInAllowedState(Entity* this) {
    // +0x94: current state (likely an enum for behavior states: idle=0, patrol=5, follow=6)
    int state = *(int*)((int)this + 0x94);
    return (state == 0 || state == 5 || state == 6);
}