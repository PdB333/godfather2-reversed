// FUNC_NAME: EARSObjectBase::setModeAndCheckCondition
bool __thiscall EARSObjectBase::setModeAndCheckCondition(EARSObjectBase* this, int value, int mode) {
    // +0x94: some property (e.g., extra data or parameter)
    *(int*)((char*)this + 0x94) = value;
    // +0x9c: mode/type field
    *(int*)((char*)this + 0x9c) = mode;

    if (mode == 3) {
        // special case: force +0x98 to 4, then check equality to 3 (will be false)
        *(int*)((char*)this + 0x98) = 4;
        return *(int*)((char*)this + 0x98) == 3;
    }

    // Otherwise, call a helper which returns some other EARSObjectBase* based on a boolean flag
    EARSObjectBase* other = FUN_0047e320(mode == 0); // likely returns a related object
    // Check if that object's +0x98 equals 3
    return *(int*)((char*)other + 0x98) == 3;
}