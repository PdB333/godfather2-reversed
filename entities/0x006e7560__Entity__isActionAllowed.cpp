// FUNC_NAME: Entity::isActionAllowed
bool Entity::isActionAllowed() {
    char canProceedGlobal = FUN_00716780();
    if (canProceedGlobal != '\0') {
        return false;
    }
    char canProceedLocal = FUN_006e7470((int)this);
    return canProceedLocal == '\0';
}