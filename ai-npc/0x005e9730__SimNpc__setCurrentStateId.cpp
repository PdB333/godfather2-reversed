// FUNC_NAME: SimNpc::setCurrentStateId
int __thiscall SimNpc::setCurrentStateId(int this, int newStateId)
{
    // +0x484: current state ID
    // +0x480: previous/finalized state ID
    if (newStateId != *(int *)(this + 0x484)) {
        *(int *)(this + 0x484) = newStateId;
        // FUN_005e8900 - validates the new state (returns 0 on failure)
        if (!isStateValid()) {
            return 0;
        }
        *(int *)(this + 0x480) = *(int *)(this + 0x484);
    }
    return 1;
}