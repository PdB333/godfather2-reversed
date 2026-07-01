// FUNC_NAME: Entity::setCurrentTarget
void __thiscall Entity::setCurrentTarget(int targetID, bool notify) {
    int *targetData;
    int oldTarget;

    targetData = getEntityData(targetID);                    // FUN_008c74d0: convert ID to data ptr
    oldTarget = this->currentTargetID;                       // +0xC8 (200)

    if ((this->stateFlags > 2) && (this->state == 3) &&     // +0xD0, +0xB0
        ((this->flags >> 2 & 1) == 0) &&                    // +0x5c bit2
        ((this->flags >> 6 & 1) == 0) &&                    // +0x5c bit6
        (oldTarget != targetID)) {
        if (getEntityData(oldTarget) != 0) {
            onTargetChanged();                               // FUN_008c1190: pre-change notification
        }
    }

    this->currentTargetID = targetID;                        // +0xC8
    this->state = *(int *)(targetData + 0x50);               // +0xB0

    if ((notify) && (this->listener != 0) &&                 // +0x9C
        (this->listener != (BaseListener*)-0x48)) {          // sentinel check
        int *vtablePtr = (int *)((int)this->listener - 0x48); // offset to base vtable
        (**(void (__thiscall **)(int))(*(int *)vtablePtr + 0x1C4))(targetID); // virtual notify call
    }

    if ((this->stateFlags > 2) && (this->state == 3) &&
        ((this->flags >> 2 & 1) == 0) &&
        ((this->flags >> 6 & 1) == 0) &&
        (oldTarget != targetID)) {
        onTargetChangedPost();                               // FUN_008c5460: post-change notification
    }
}