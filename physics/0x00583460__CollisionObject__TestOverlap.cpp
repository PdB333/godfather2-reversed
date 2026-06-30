// FUNC_NAME: CollisionObject::TestOverlap
int __thiscall CollisionObject::TestOverlap(CollisionObject* other) {
    // +0x40 appears to be a collision enable/disable flag
    if (this != 0 && other != 0) {
        int savedThisFlag = *(int*)((char*)this + 0x40);
        int savedOtherFlag = *(int*)((char*)other + 0x40);
        // Temporarily disable collision on both objects to allow an overlap test
        *(int*)((char*)this + 0x40) = 0;
        *(int*)((char*)other + 0x40) = 0;
        int result = FUN_00585450(); // Performs the actual overlap detection
        // Restore collision flags
        *(int*)((char*)this + 0x40) = savedThisFlag;
        *(int*)((char*)other + 0x40) = savedOtherFlag;
        FUN_0056f740(); // Post-test cleanup or state update
        return result;
    }
    return 0;
}