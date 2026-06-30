// FUNC_NAME: Player::checkInteractableObjectState
bool __thiscall Player::checkInteractableObjectState(int this, int inputParam) {
    bool bResult = false;
    int resolvedId = FUN_004025a0(inputParam); // probably maps input to entity ID (e.g. controller slot -> entity)
    int entityId;
    if (resolvedId == 0) {
        entityId = 0xfe16702f; // invalid/empty entity marker
    } else {
        entityId = *(int *)(resolvedId + 0x2c); // get entity ID from resolved object
    }
    int objectData = FUN_0088dbb0(entityId); // fetch object's state block by ID
    if (objectData != 0) {
        int stateFlagsPtr = *(int *)(objectData + 0x14); // +0x14 points to per-instance flags
        bResult = (*(byte *)(stateFlagsPtr + 0x51) & 4) != 0; // test bit2: "interactable" flag
        if (bResult) {
            *(uint *)(this + 0x1f58) |= 0x40000000; // set bit30 in player InteractionFlags1
        }
        if (*(char *)(stateFlagsPtr + 0x50) == 3) { // state == ACTIVE_INTERACTION_STATE
            *(uint *)(this + 0x1f5c) |= 0x80; // set bit7 in player InteractionFlags2
            return true;
        }
    }
    return bResult;
}