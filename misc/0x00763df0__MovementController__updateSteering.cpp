// FUNC_NAME: MovementController::updateSteering
// Address: 0x00763df0
// Role: Updates the movement steering logic, computing distance to target or random drift,
// and adjusting orientation based on velocity.

void __thiscall MovementController::updateSteering(uint this) {
    // Get global physics state (probably player or reference point)
    int globalState = getGlobalState(); // FUN_00471610
    Vector3 worldTarget;
    worldTarget.x = *(float*)(globalState + 0x30);
    worldTarget.y = *(float*)(globalState + 0x34);
    worldTarget.z = *(float*)(globalState + 0x38);

    globalState = getGlobalState(); // again
    Vector3 worldPos;
    worldPos.x = *(float*)(globalState + 0x20);
    worldPos.y = *(float*)(globalState + 0x24);
    worldPos.z = *(float*)(globalState + 0x28);

    // Set state to 3 (maybe "moving" or "steering")
    *(int*)(this + 0xDC) = 3;

    // If bit 4 of flags is clear, set up a target from world vectors
    if ((*(uint*)(this + 0xE8) & 0x10) == 0) {
        computeTargetFromVectors(this + 0x5C, &worldTarget, &worldPos, 0, this + 0x68); // FUN_00600a40
    }

    // Set flag 0x400 on the transform structure
    uint* transformFlags = (uint*)(*(int*)(this + 0x78) + 0xB4);
    *transformFlags |= 0x400;

    float speed;
    if ((*(int*)(this + 0x5C) == 0) ||
        (*(int*)(this + 0x64) == 0 && *(int*)(this + 0x68) == 0)) {
        // No target or path — apply random drift based on time * speed factor
        float speedFactor = *(float*)(this + 0xA4); // magnitude
        double randomScalar = getRandomScalar(); // FUN_005fe710
        float drift = (float)(randomScalar * (double)speedFactor);
        speed = drift;
        if (drift >= 0.0f) {
            *(uint*)(this + 0xE8) |= 1; // positive direction
        } else {
            *(uint*)(this + 0xE8) &= 0xFFFFFFFE;
        }
        *(float*)(this + 0xD4) = speed;
    } else {
        // Compute distance to target
        int state2 = getGlobalState();
        Vector3 target = { *(float*)(this + 0x64), *(float*)(this + 0x68), *(float*)(this + 0x70) }; // from this's target fields
        float sqDist = computeSquaredDistance(state2 + 0x30, &target, 0, 1); // FUN_0084cb90
        float distance = sqrtf(sqDist);
        *(float*)(this + 0xD4) = distance;
        if (distance >= 0.0f) {
            *(uint*)(this + 0xE8) |= 1;
        } else {
            *(uint*)(this + 0xE8) &= 0xFFFFFFFE;
        }
        speed = distance;
    }

    // Read orientation from transform structure
    uint* transform = *(uint**)(this + 0x78); // pointer to transform structure
    float orientation0 = *(float*)transform;   // +0: first orientation component
    float orientation1 = *(float*)(transform + 1); // +4: second? Actually +1 on uint* is +4 bytes? Must be careful.
    // But decompiler shows reading 8 bytes at once, then 4 bytes at offset 8. Adjust:
    // Actually: *(undefined8 *)(this + 0xC8) = **(undefined8 **)(this + 0x78); -> 8 bytes at offset 0 of transform.
    // Then uVar4 = *(undefined4 *)( *(undefined8 **)(this + 0x78) + 1); -> +8 bytes.
    // So orientation0 is first 4 bytes, orientation1 is next 4, and then there is a third component at +8.
    // We'll treat it as a quaternion or direction vector with at least 3 components.
    float orientX = *(float*)transform; // +0
    float orientY = *(float*)((char*)transform + 4); // +4
    float orientZ = *(float*)((char*)transform + 8); // +8 (stored later as DWORD at this+0xD0)

    // Copy orientation (first 8 bytes) to this+0xC8 and the third component to this+0xD0
    *(uint64*)(this + 0xC8) = *(uint64*)transform; // copies orientX and orientY
    *(float*)(this + 0xD0) = orientZ;

    // If speed is not near zero (global epsilon)
    float epsilon = *(float*)0x00d577a0; // likely near-zero constant
    if (fabs(speed - epsilon) > 1e-6f) { // actually check inequality directly
        // Adjust orientation by velocity
        float rotationFactor = *(float*)((char*)transform + 0xF8); // some rotation factor
        double delta = (double)rotationFactor;
        applyRotation1(); // FUN_00b99e20 - subtract part
        double delta2 = (double)rotationFactor;
        // Update orientation components
        *(float*)(this + 0xC8) = orientX - (float)delta * speed;
        applyRotation2(); // FUN_00b99fcb - add part
        *(float*)(this + 0xD0) = (float)delta2 * speed + orientZ;
    }
}