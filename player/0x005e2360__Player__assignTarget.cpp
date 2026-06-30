// FUNC_NAME: Player::assignTarget
bool __thiscall Player::assignTarget(uint param_1) {
    // +0x1744: flag indicating if targeting is allowed (byte)
    if (*(byte*)(this + 0x1744) != 0) {
        // Retrieve or allocate a target slot object (returns nullptr if none available)
        TargetSlot* slot = (TargetSlot*)getTargetSlot();
        if (slot != nullptr) {
            // +0x24c: target identifier (entity ID or pointer) to store
            slot->targetId = param_1;
            return true;
        }
    }
    return false;
}