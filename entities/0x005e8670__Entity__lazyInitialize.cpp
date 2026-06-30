// FUNC_NAME: Entity::lazyInitialize
void Entity::lazyInitialize(void) {
    // Check if already initialized using flag at +0x490
    if (*(char *)(this + 0x490) == '\0') {
        // Call the real initialization routine
        FUN_005e8300(this);
        // Mark as initialized
        *(char *)(this + 0x490) = 1;
    }
}