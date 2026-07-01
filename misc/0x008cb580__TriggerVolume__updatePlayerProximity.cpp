// FUNC_NAME: TriggerVolume::updatePlayerProximity
void __thiscall TriggerVolume::updatePlayerProximity(int *triggerState) {
    // param_1 (this) is a TriggerVolume*; at +0x24: position.x, +0x28: position.y, +0x2c: position.z, +0x30: radius, +0x34: flags (bit0 = inside)
    // param_2: pointer to a trigger state (likely per-player or per-instance state)
    processTriggerStateNode(triggerState); // FUN_004b6f20 - likely updates state node from data

    // Global trigger ID for checking if this volume should be processed
    if (DAT_012069d4 == *triggerState) {
        float distance = *(float*)0x00d7c2cc; // default distance threshold
        // Check if there's a valid player/camera entity
        int* entityManager = *(int**)0x012233a0; // pointer to some manager
        if (entityManager != nullptr && entityManager[1] != (int)0x1f30) { // +4 offset: entity count or something
            int playerEntity = FUN_00471610(); // returns a pointer to player entity or camera
            // Compute distance from player to this trigger volume
            float dx = *(float*)(this + 0x24) - *(float*)(playerEntity + 0x30);
            float dy = *(float*)(this + 0x28) - *(float*)(playerEntity + 0x34);
            float dz = *(float*)(this + 0x2c) - *(float*)(playerEntity + 0x38);
            distance = sqrtf(dx*dx + dy*dy + dz*dz) - *(float*)(this + 0x30); // distance minus radius
        }
        // Check flags: bit0 = inside flag (0 = outside, 1 = inside)
        if ((*(byte*)(this + 0x34) & 1) == 0) {
            // Currently outside the trigger volume
            if (distance <= *(float*)0x00d7c2cc) {
                // Distance is within threshold, trigger enter
                int offset = (this == (TriggerVolume*)0xc) ? 0 : (int)this + 0x20;
                onTriggerEnter((TriggerVolume*)offset, distance); // FUN_008cb3c0
            }
        } else {
            // Currently inside the trigger volume
            if (*(float*)0x00d7c2c8 < distance) {
                // Distance exceeded exit threshold, trigger exit
                int offset = (this == (TriggerVolume*)0xc) ? 0 : (int)this + 0x20;
                onTriggerExit((TriggerVolume*)offset, distance); // FUN_008cb400
            }
        }
    }
}