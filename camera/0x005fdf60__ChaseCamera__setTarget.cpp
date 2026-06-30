// FUNC_NAME: ChaseCamera::setTarget

void ChaseCamera::setTarget(Entity *target, int timestamp) {
    int *smartPtr = (int *)(this + 0x118);

    // Release existing target reference, if any
    if ((*(int *)(this + 0x118) != 0) && (*smartPtr != 0)) {
        releaseObjectRef(smartPtr);  // FUN_004daf90
        *smartPtr = 0;
    }

    if (target != nullptr) {
        // Only reassign if target differs from current
        if ((int *)*smartPtr != target) {
            if ((int *)*smartPtr != nullptr) {
                releaseObjectRef(smartPtr);
            }
            *smartPtr = (int)target;
            *(int *)(this + 0x11c) = target->refCount; // +0x04 in Entity?
            target->refCount = (int)smartPtr;          // +0x04 assigned to this pointer?
        }

        // Store additional parameter (likely a timestamp or sequence number)
        *(int *)(this + 0x120) = timestamp;

        // Get position from target's transform via virtual calls
        int result1 = (*(target->vtable + 8))();        // vtable[2] -> GetObjectID?
        int handle = (*(target->vtable + 0xc))(result1 - 1); // vtable[3] -> GetTransformHandle?
        int *pMatrix = *(int **)handle;                // Dereference handle

        // If matrix is valid, copy translation into this->targetPosition
        if (*pMatrix != 0) {
            float *pos = (float *)pMatrix[2];          // +0x08: translation component of transform
            *(float *)(this + 0x130) = pos[0];
            *(float *)(this + 0x134) = pos[1];
            *(float *)(this + 0x138) = pos[2];
        }
    }
}