// FUNC_NAME: Entity::getInitializedValue
int __thiscall Entity::getInitializedValue(Entity* this) {
    // If the flag at +0x8c is zero, perform initialization via FUN_0061e810
    if (*(char*)((uintptr_t)this + 0x8c) == '\0') {
        FUN_0061e810((int)this);
    }
    // Return the value at +0x4 (likely a handle, pointer, or identifier)
    return *(int*)((uintptr_t)this + 4);
}