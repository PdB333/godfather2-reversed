// FUNC_NAME: PlayerStateMachine::handleLookAtEvent
void __thiscall PlayerStateMachine::handleLookAtEvent(int this, void* event) {
    // Dereference event's vtable and call the first virtual function to get event ID
    int eventId = (**(int (__thiscall**)(void*))(*(int*)event))();
    if (eventId == 0x27a0f69c) { // kEventUpdateLookAt
        // Get a pointer to some singleton (e.g., camera manager)
        int singletonBase = FUN_00471610(); // getCameraManager or getPlayer
        bool invert = false;
        int state = *(int*)(this + 0x5c); // +0x5c: player state (0 = normal, 0x48 = aiming)
        int singleton2;
        undefined8 lookDir; // packed (x,y) floats
        float lookZ;

        if (state == 0 || state == 0x48) {
            // Normal or aiming state: read look direction from singleton
            singleton2 = FUN_00471610(); // same singleton? Actually different because we read different offsets
            lookDir = *(undefined8*)(singleton2 + 0x20); // +0x20: look direction X/Y
            lookZ = *(float*)(singleton2 + 0x28); // +0x28: look direction Z
        } else {
            // Other state: also read but set invert flag
            singleton2 = FUN_00471610();
            lookDir = *(undefined8*)(singleton2 + 0x20);
            lookZ = *(float*)(singleton2 + 0x28);
            invert = true;
        }

        // Distance factor from camera transform
        float distance = *(float*)(*(int*)(this + 0x50) + 0x1ec0); // this->cameraTransform->distance

        // Calculate new camera position: targetPos + lookDir * distance
        // targetPos is from singletonBase (iVar3) at +0x30, +0x34, +0x38
        float newX = (float)lookDir * distance + *(float*)(singletonBase + 0x30); // +0x30: target position X
        float newY = *(float*)((int)&lookDir + 4) * distance + *(float*)(singletonBase + 0x34); // +0x34: target position Y
        float newZ = lookZ * distance + *(float*)(singletonBase + 0x38); // +0x38: target position Z

        if (invert) {
            // Invert look direction for certain states (e.g., aiming backward?)
            lookZ = DAT_00e44564 - lookZ;
            lookDir = CONCAT44(DAT_00e44564 - *(float*)((int)&lookDir + 4), DAT_00e44564 - (float)lookDir);
        }

        // Call function to set camera transform (position and look direction)
        // Parameters: new position (vec3), look direction (vec3), bool1, global, bool2, bool3
        FUN_00754d30(&newX, &lookDir, 1, _DAT_00d64c8c, 0, 1);

        // Reset the distance to zero (consumed)
        *(float*)(*(int*)(this + 0x50) + 0x1ec0) = 0.0f;
    }
}