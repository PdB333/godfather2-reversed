// FUNC_NAME: Projectile::isPathClear
// Function at 0x00714770: Checks if a line from given start position along the projectile's forward direction is clear of any blocking objects.
// Returns 1 if clear, 0 if blocked.

bool __thiscall Projectile::isPathClear(const Vector3& startPos) {
    char isBlocking;
    Vector3 thisForward;
    Vector3 ownPos;
    Vector3 startToObj;
    Vector3 objPos;
    Vector3 parentObjPos; // from obj's parent pointer at +0x933
    Vector3 otherPos;     // from this->owner->target at +0x24cc
    float timeScale = gTimeDelta; // DAT_00d61a04
    float extraScale = gExtraScale; // _DAT_00d5c458
    float threshold = gThreshold;   // _DAT_00d577a0

    // Get this projectile's forward direction from its owner (at +0x10)
    // Virtual call at vtable+0x40 returns forward vector into thisForward.x and ..something?
    // Actually the function returns two floats: local_20 and local_44.
    // Due to decompiler artifacts, we treat the call as GetForward with output in fwd (x,z) 
    thisForward.x = 0.0f; // placeholder, replace with actual call
    thisForward.z = 0.0f; // placeholder

    // Compute extended target points: one based on forward.x, one based on forward.z
    // The code computes two points: one offset by forward.x*timeScale, another by forward.z*timeScale
    // and also interpolates between them.
    Vector3 target1 = startPos + Vector3(thisForward.x * timeScale, 0.0f, thisForward.z * timeScale);
    Vector3 target2 = startPos + Vector3(thisForward.z * timeScale, 0.0f, thisForward.x * timeScale);
    Vector3 midpoint = startPos + Vector3(0.0f, 0.0f, (thisForward.z - thisForward.x) * extraScale);

    // Use target1 as the line endpoint (maybe final aim point)
    // Actually the code uses uStack_98 and uStack_8c, which we'll simplify as two points.

    // Get list of all sim objects
    SimObjectList* pList = GetSimObjectList(); // FUN_00806460
    ListIterator it = pList->begin(); // FUN_0043c2c0 returns pointer to first node

    while (it != pList->end()) {
        uint hashResult;
        char cVar1 = it->checkHash(0x369ac561, &hashResult); // virtual at vtable+0x10
        if (cVar1) {
            SimObject* pObj = (SimObject*)hashResult;
            if (pObj != this->owner && pObj != nullptr && (pObj->flags & 0x1) != 0) {
                // Get object's world position
                pObj->getPosition(objPos); // virtual at vtable+0x48

                Vector3 relPos = objPos - startPos;
                
                // Check if object has a parent at +0x933 (some attachment)
                SimObject* pParent = pObj->parent; // offset +0x933
                if (pParent != nullptr) {
                    pParent->getPosition(parentObjPos);
                    // Check if relative vector from start to obj is "behind" the parent
                    // dot(relPos, parentObjPos - objPos) < 0
                    Vector3 parentToObj = objPos - parentObjPos;
                    if (dotProduct(relPos, parentToObj) < 0.0f) {
                        // Additional line-of-sight check using target points
                        if (!isLineClear(relPos, target1, target2)) {
                            return 0; // blocked
                        }
                    }
                }

                // Check secondary condition: this->owner->target (at +0x24cc)
                SimObject* pTarget = this->owner->target; // from *(*(this+0x10)+0x24cc)
                if (pTarget != nullptr) {
                    pTarget->getPosition(otherPos);
                    // Check if dot(relPos, otherPos - startPos) > threshold
                    Vector3 otherDir = otherPos - startPos;
                    if (dotProduct(relPos, otherDir) > threshold) {
                        // Also check using the object's own forward direction
                        pObj->getForward(); // virtual at vtable+0x40, stores into some stack
                        // Get some transforms from FUN_00471610
                        Matrix4 boneTransform = getBoneTransform(); // call twice
                        // Check if the line between startPos and otherPos intersects something
                        Vector3 lineStart = otherPos; // actually from stack
                        Vector3 lineEnd = otherPos; // computed
                        if (isLineIntersected(lineStart, lineEnd)) {
                            return 0;
                        }
                    }
                }
            }
        }
        it = it->next;
    }
    return 1;
}