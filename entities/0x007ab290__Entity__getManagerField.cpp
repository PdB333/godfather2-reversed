// FUNC_NAME: Entity::getManagerField
int Entity::getManagerField() const {
    // Dereference pointer at +0x58 (likely a manager or singleton)
    // then read int at +0x1eb8 from that manager
    return *(int*)(*(int*)((uintptr_t)this + 0x58) + 0x1eb8);
}