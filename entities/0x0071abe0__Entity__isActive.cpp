// FUNC_NAME: Entity::isActive
bool __thiscall Entity::isActive(void) {
    // Check if both component pointers (offsets +0x10 and +0x20) are null
    if ((*(int *)((char *)this + 0x10) == 0) && (*(int *)((char *)this + 0x20) == 0)) {
        return false;  // No component active
    }
    return true;  // At least one component present
}