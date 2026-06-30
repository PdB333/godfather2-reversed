// FUNC_NAME: Entity::isValid
__thiscall byte Entity::isValid(int* this) {
    // Checks if the entity has a valid vtable (+0x00) and a valid resource pointer (+0x08)
    if (this[0] != 0 && this[2] != 0) {
        return 1;
    }
    return 0;
}