// FUNC_NAME: EntityBase::canUpdate
bool EntityBase::canUpdate(int entityHandle) {
    char result;

    result = FUN_00716780();  // presumably checks global game state (paused, UI active?)
    if (result != '\0') {
        return false;
    }

    result = FUN_006e7470(entityHandle);  // checks per-entity condition (e.g., alive, valid)
    return result == '\0';
}