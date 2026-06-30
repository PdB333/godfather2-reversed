// FUNC_NAME: Entity::releaseIfAllocated
void __thiscall Entity::releaseIfAllocated() {
    // +0xd0: pointer to allocated resource or handle
    if (*(int*)(this + 0xd0) != 0) {
        // Release the resource (argument 0 indicates which resource or mode)
        FUN_004df830(0);
    }
}