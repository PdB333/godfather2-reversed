// FUNC_NAME: AICharacter::updatePathAction
void __fastcall AICharacter::updatePathAction(int this)
{
    int *listHeadPtr;
    int oldPathNode;
    int oldFinalNode;
    int oldNextNode;
    char actionFound;
    int actionData;
    int actionPtr;
    float *currentPos;
    int tempTransform;
    float distanceSq;
    float dx;
    float dz;
    float dy;
    float speedSq;
    float speed;
    float overrideSpeed;
    float dX2;
    float dY2;
    float dZ2;
    uint index;
    int *nodeList;

    // Get current transform from the game's camera/player manager
    tempTransform = getCurrentTransform();
    currentPos = (float *)(tempTransform + 0x30); // +0x30: position vector (x,y,z)
    transform = getCurrentTransform(); // second call, maybe different instance
    oldPathNode = *(int *)(this + 0x1b8);   // +0x1b8: pointer to current path node
    oldFinalNode = *(int *)(this + 0x1c0);    // +0x1c0: pointer to final target node?
    oldNextNode = *(int *)(this + 0x1bc);     // +0x1bc: pointer to next node in path

    // Sync orientation with target direction (e.g., face movement direction)
    setOrientationToTarget(currentPos, transform + 0x20, 1);
    lerpOrientation(currentPos, this + 0x19c, DAT_00d6112c); // +0x19c: orientation quaternion?

    // Manage action list: if the current path node has changed, update the head pointer
    listHeadPtr = (int *)(this + 0x194);   // +0x194: pointer to list head (action list?)
    if (*(int *)(this + 0x194) != oldPathNode) {
        if (*(int *)(this + 0x194) != 0) {
            releaseActionNode(listHeadPtr); // +0x194: pointer to list head
        }
        *listHeadPtr = oldPathNode;
        if (oldPathNode != 0) {
            *(int *)(this + 0x198) = *(int *)(oldPathNode + 4); // +0x198: next pointer in node
            *(int **)(oldPathNode + 4) = listHeadPtr;           // set prev pointer of new head
        }
    }

    // If we have a valid action list head
    if (*listHeadPtr != 0) {
        actionFound = queryActionData(*(short *)(*listHeadPtr + 0x4c), 0xf38150a, &actionData);
        // actionData returns pointer to data and actionPtr (maybe offset)
        if ((((actionFound == 0) || (actionPtr == 0)) || (actionData == 0)) ||
           ((*(char *)(actionData + 6) != 3 || (distanceSq = *actionPtr, distanceSq <= 0.0)))) {
            // If invalid, use the fallback speed from +0x36c
            *(float *)(this + 0x370) = *(float *)(this + 0x36c); // +0x370: current speed? +0x36c: base speed
        } else {
            // Valid bullet/projectile data: square the radius to get speed
            *(float *)(this + 0x370) = distanceSq * distanceSq;
        }

        // If we have a next node to move towards
        if (*(int *)(this + 0x1bc) != 0) {
            resetSteeringState();

            // Set up a move-to action
            *(int *)(this + 0x288) = *(int *)(this + 0x1bc); // +0x288: target node?
            *(int *)(this + 0x2b0) = 0;                      // +0x2b0: action flags?
            *(int *)(this + 0x28c) = *(int *)(this + 0x1c0); // +0x28c: final target

            // Compute distance to target position (stored at +0x1d4, +0x1d8, +0x1dc)
            dx = *currentPos - *(float *)(this + 0x1d4);
            dy = *(float *)(transform + 0x34) - *(float *)(this + 0x1d8);
            dz = *(float *)(transform + 0x38) - *(float *)(this + 0x1dc);
            *(float *)(this + 0x2b4) = sqrt(dx*dx + dy*dy + dz*dz); // +0x2b4: distance to target

            // Set action type to 2 (move/seek)
            *(int *)(this + 0x284) = 2; // +0x284: action type?
            executeAction((int *)(this + 0x284),   // action type
                          this + 0x288,            // target node
                          0,                      // optional parameter
                          this + 0x2b0,            // flags
                          *(int *)(this + 0x1c0),  // final target
                          *(float *)(this + 0x64)); // speed factor

            // Now set up a "follow" action toward the next intermediate waypoint
            *(int *)(this + 0x20c) = *(int *)(this + 0x1c0); // +0x20c: waypoint pointer
            *(int *)(this + 0x25c) = 0;                       // +0x25c: action flags
            *(int *)(this + 0x210) = *(int *)(this + 0x1bc);  // +0x210: next node

            // Compute distance to intermediate waypoint (stored at +0x1c8, +0x1cc, +0x1d0)
            dx = *currentPos - *(float *)(this + 0x1c8);
            dy = *(float *)(transform + 0x34) - *(float *)(this + 0x1cc);
            dz = *(float *)(transform + 0x38) - *(float *)(this + 0x1d0);
            *(float *)(this + 0x260) = sqrt(dx*dx + dy*dy + dz*dz); // +0x260: distance to waypoint

            overrideSpeed = *(float *)(this + 0x64); // +0x64: base speed/acceleration
            *(int *)(this + 0x208) = 2; // action type again

            // Check for special conditions: not in god mode and has special flag
            if (((*(byte *)(this + 0x428) & 1) == 0) && ((*(uint *)(this + 0x170) >> 1 & 1) != 0)) {
                overrideSpeed = *(float *)(DAT_011298e4 + 0xc4); // global override (e.g., difficulty multiplier)
            }
            if (overrideSpeed < DAT_00e448cc) {
                overrideSpeed = DAT_00e448cc; // minimum speed clamp
            }

            // Execute the follow action with the speed
            executeAction((int *)(this + 0x208),   // action type
                          this + 0x20c,            // waypoint pointer
                          this + 0x234,            // unknown (maybe other parameter)
                          this + 0x25c,            // flags
                          *(int *)(this + 0x1bc),  // next node
                          overrideSpeed);

            // If any of the pointer fields changed, notify listeners (repath needed?)
            if (((*listHeadPtr != oldPathNode) ||
                (*(int *)(this + 0x1c0) != oldFinalNode) ||
                (*(int *)(this + 0x1bc) != oldNextNode)) &&
                (*(int *)(this + 0x98) != 0)) {          // +0x98: number of listeners
                nodeList = *(int **)(this + 0x94);       // +0x94: array of listener pointers
                for (index = 0; index < *(uint *)(this + 0x98); index++) {
                    int node = nodeList[index * 2];      // each listener entry is 8 bytes?
                    if ((node != 0) && (node != 0x48)) {
                        notifyActionChanged();
                    }
                }
            }
        }
    }
    return;
}