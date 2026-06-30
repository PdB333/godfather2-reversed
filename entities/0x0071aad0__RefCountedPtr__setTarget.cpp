// FUNC_NAME: RefCountedPtr::setTarget
// Address: 0x0071aad0
// Role: Sets the target pointer with reference counting and intrusive list management.
// Fields: +0x0c = m_resourceHandle (some ID), +0x18 = m_targetPtr (current target), 
// +0x1c = m_savedNext (used during link), +0x3c = m_flags (bit1 = needRelease?)

void __thiscall RefCountedPtr::setTarget(int newTarget) {
    int *targetPtr = (int *)(this + 0x18); // pointer to the current target field

    // Self-assignment check: if the new target is the same as the current one and non-null
    if ((newTarget == *targetPtr) && (newTarget != 0)) {
        char resActive = isResourceActive(*(this + 0xc)); // check if resource is already active
        if (resActive == 0) {
            char canChange = canChangeTarget(newTarget); // verify that changing to this target is allowed
            if (canChange == 0) {
                // Both checks failed: clear bit 1 in flags (assuming bit1 = needRelease or hasChanges)
                *(uint *)(this + 0x3c) = *(uint *)(this + 0x3c) & 0xfffffffd;
                goto after_self_check;
            }
        }
    }
after_self_check:
    // If the new target is different from the current one, release old target and set new
    if (*targetPtr != newTarget) {
        if (*targetPtr != 0) {
            releaseRef(targetPtr);
            *targetPtr = 0;
        }
        *targetPtr = newTarget;
        if (newTarget != 0) {
            // Save the next pointer from the new target into our saved field at +0x1c
            *(int *)(this + 0x1c) = *(int *)(newTarget + 4);
            // Set the new target's next pointer to point to our target pointer slot
            // (intrusive list: each node's +4 holds address of the pointer that points to it)
            *(int **)(newTarget + 4) = targetPtr;
        }
    }
    // If we have a valid new target, perform a reference increment if resource is still valid
    if (*targetPtr != 0) {
        char stillValid = isTargetReferenced(*(this + 0xc));
        if (stillValid != 0) {
            modifyRefCount(1, *(this + 0xc)); // increment reference count on the resource
        }
    }
    return;
}