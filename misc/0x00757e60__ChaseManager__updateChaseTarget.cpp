// FUNC_NAME: ChaseManager::updateChaseTarget
void __thiscall ChaseManager::updateChaseTarget(float deltaTime, float* outTargetPos) {
    // this+0x100: m_pTarget (pointer to target struct with position, state)
    // this+0x130: m_activeChaseState (int)
    // this+0x14c: m_chaseStateTransitionCount (int)
    // this+0xa8: m_flags (bitfield)
    // Target struct offsets:
    //   +0x00: position (float[3])
    //   +0x88: m_stateIndexA (int)
    //   +0x90: m_stateIndexB (int)
    //   +0xb0: m_followDistance (float)
    //   +0xb4: m_targetFlags (uint, bit0 = active)

    Target* target = *(Target**)(this + 0x100);
    if (!target) {
        return;
    }

    // Copy target position to output
    outTargetPos[0] = target->position[0];
    outTargetPos[1] = target->position[1];
    outTargetPos[2] = target->position[2];

    // Get player/camera position (likely returns x,z in buffer, y ignored)
    float camPos[3]; // Actually local_4c[0]=x, local_4c[1]=y, local_44=z, but we assume 3 floats
    getCameraPosition(camPos); // FUN_007577e0

    // 2D distance (XZ plane) between camera and target
    float dx = camPos[0] - outTargetPos[0];
    float dz = camPos[2] - outTargetPos[2]; // camPos[2] is local_44 (z)
    float dist2D = sqrt(dx*dx + dz*dz);

    // Get velocity magnitude (unknown source)
    Vector3 velocity; // local_3c, local_38, local_40
    getVelocityVector(&velocity, 0); // FUN_0045ec00
    float speed = sqrt(velocity.x*velocity.x + velocity.y*velocity.y + velocity.z*velocity.z);

    // If target is active and distance is less than speed * some factor, deactivate target
    if ((target->m_targetFlags & 1) != 0 && dist2D < speed) {
        target->m_targetFlags &= ~1;
        *(int*)(this + 0x130) = 2; // Set state to "lost" or "stopped"
        return;
    }

    // Compute follow distance threshold
    float threshold = DAT_00d5ccf8; // global constant
    if (dist2D < speed + DAT_00d64f1c) {
        threshold = speed / deltaTime + DAT_00d64f1c;
    }
    target->m_followDistance = threshold;

    // Build decision buffer
    DecisionBuffer buffer; // local_24 - stack struct
    buildDecisionBuffer(&buffer, 2); // FUN_0075d650, 2 = size or type

    // Cache previous state index
    int prevStateIndex = (target->m_stateIndexA != 0) ? target->m_stateIndexB : 0;

    // Evaluate chase state
    int newState = updateChaseStateMachine(deltaTime, 1, 1, &buffer); // FUN_00600210
    *(int*)(this + 0x130) = newState;

    // Check if state index changed
    int curStateIndex = (target->m_stateIndexA != 0) ? target->m_stateIndexB : 0;
    if (curStateIndex != prevStateIndex) {
        *(int*)(this + 0x14c) += 1; // Increment transition counter
        *(unsigned int*)(this + 0xa8) |= 0x80000; // Set some flag (e.g., "stateChanged")
    }
}