// FUNC_NAME: Entity::releasePointerSet
void __thiscall Entity::releasePointerSet(int this) {
    // +0x4c: pointer to a sub-object or resource
    if (*(int *)(this + 0x4c) != 0) {
        FUN_009c8f10(*(int *)(this + 0x4c)); // release the sub-object
    }
    FUN_005c16e0(); // global or base cleanup
    return;
}