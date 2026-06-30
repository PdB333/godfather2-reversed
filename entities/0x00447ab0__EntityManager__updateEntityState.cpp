// FUNC_NAME: EntityManager::updateEntityState

void __thiscall EntityManager::updateEntityState(int entityID, char isActive, char triggerCallback)
{
    // +0xB4: count of entries in the entity list
    // +0xB0: pointer to an array of 8-byte entries (each likely {int id, int flags})
    int count = *(int *)(this + 0xB4);
    int index = count - 1;
    if (index >= 0) {
        int *entry = (int *)(*(int *)(this + 0xB0) + index * 8);
        do {
            if (*entry == entityID) {
                // Found matching entity – deactivate it
                EntityManager::deactivateEntity(entityID, 0);
                break;
            }
            index--;
            entry -= 2; // Go to previous 8-byte entry (two ints backwards)
        } while (index >= 0);
    }

    // Apply state transition based on isActive flag
    if (isActive == '\0') {
        // Deactivate (state = 2)
        EntityManager::setEntityState(entityID, 2);
        if (triggerCallback != '\0') {
            EntityManager::startEntityAction(this, entityID);
        }
    } else {
        // Activate (state = 1)
        EntityManager::setEntityState(entityID, 1);
        if (triggerCallback != '\0') {
            EntityManager::finalizeEntityAction(entityID);
            return;
        }
    }
}