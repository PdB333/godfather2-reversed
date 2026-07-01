// FUNC_NAME: Entity::isValidTarget
bool __thiscall Entity::isValidTarget(int thisPtr, int targetEntity) {
    char result;

    // Check if target is directly valid (e.g., alive, in range)
    result = FUN_0083ce40(targetEntity);
    if (result != 0) {
        return true;
    }

    // If this entity's flags bit 14 is not set (e.g., not disabled/dead),
    // check an alternative condition (e.g., can be interacted with)
    if (((*(uint *)(thisPtr + 0xa8) >> 0xe) & 1) == 0) {
        result = FUN_0083bb40(targetEntity);
        if (result != 0) {
            return true;
        }
    }

    return false;
}