// FUNC_NAME: Entity::isActive
bool Entity::isActive(void *this) {
    char result;
    result = (**(code **)(*(int *)DAT_01223510 + 0x34))(this);
    return result != '\0';
}