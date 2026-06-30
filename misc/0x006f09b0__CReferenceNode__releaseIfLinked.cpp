// FUNC_NAME: CReferenceNode::releaseIfLinked
void __thiscall FUN_006f09b0(CReferenceNode* thisPtr) {
    // Check that both pointers are valid and the reference count matches the target's magic
    if (thisPtr->pTarget != nullptr && thisPtr->pRefCount != nullptr &&
        *thisPtr->pRefCount == *(thisPtr->pTarget + 0x18 / sizeof(int))) {
        // Release the target object (decrement reference / deallocate)
        FUN_006fda60(0);
        // Clear all fields
        thisPtr->pTarget = nullptr;              // +0x10
        thisPtr->field_0C = 0;                   // +0x0C
        thisPtr->pRefCount = nullptr;            // +0x08
        thisPtr->field_14 = 0;                   // +0x14
        thisPtr->field_18 = 0;                   // +0x18
        thisPtr->field_1C = 0;                   // +0x1C
    }
}