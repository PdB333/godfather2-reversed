// FUNC_NAME: Entity::checkProximityTimer
void Entity::checkProximityTimer() {
    // +0x39e: flags (ushort)
    ushort flags = *(ushort*)((int)this + 0x39e);
    
    // Check if bit1 is set, bit3 is clear, bit5 is clear
    if (((flags >> 1 & 1) != 0) && ((flags >> 3 & 1) == 0) && ((flags >> 5 & 1) == 0)) {
        float local_c = 0.0f; // x
        float local_8 = 0.0f; // y
        int local_4 = 0;      // z (but stored as int, likely just placeholder)
        
        // Call virtual function at vtable+0x4c to get entity position
        // (likely getPosition(Vector3*))
        (*(void (__thiscall**)(Entity*, float*))(*(int*)this + 0x4c))(this, &local_c);
        
        // unaff_ESI holds the z component (passed in register, not stored locally)
        // Compute squared distance from origin
        float squaredDist = local_8 * local_8 + local_c * local_c + unaff_ESI * unaff_ESI;
        
        float threshold = *(float*)0x00d61440; // squared distance threshold
        if (threshold <= squaredDist) {
            // Entity is far enough away – reset timer
            *(float*)(this + 0x384) = 0.0f; // +0x384: proximityTimer
        } else {
            // Entity is too close – accumulate timer
            float dt = *(float*)0x012067e8; // global frame delta time
            float timer = *(float*)(this + 0x384) + dt;
            *(float*)(this + 0x384) = timer;
            
            float maxTimer = *(float*)0x00d61444; // max allowed time
            if (maxTimer < timer) {
                // Exceeded time – set bit5 flag and trigger callback
                *(ushort*)((int)this + 0x39e) |= 0x20;
                FUN_00402050(&DAT_0112ac64, 0); // trigger some action
                return;
            }
        }
    }
}