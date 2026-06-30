// FUNC_NAME: SimNpc::updateMovement
bool __thiscall SimNpc::updateMovement(SimNpc* thisObj, MovementData* movementData, float deltaTime) {
    bool bReturn0 = false;
    
    if (thisObj == nullptr || movementData == nullptr) {
        return false;
    }
    
    uint16_t id = *(uint16_t*)((uintptr_t)thisObj + 0x8); // +0x8: unique id
    uint16_t flags = *(uint16_t*)((uintptr_t)thisObj + 0x10); // +0x10: state flags
    
    // Check if already processing or reset
    if ((flags & 0x2) != 0) {
        *(uint16_t*)((uintptr_t)thisObj + 0x10) = flags & 0xFFFD;
        return true;
    }
    
    int movementAmount = *(int*)((uintptr_t)thisObj + 0x14); // +0x14: distance or time
    
    // Scale movement if requested
    if (*(uint8_t*)((uintptr_t)movementData + 0x12) & 0x2) { // +0x12: flags byte
        float fAmount = (float)movementAmount;
        if (movementAmount < 0) {
            fAmount += 0.5f; // DAT_00e44578 likely 0.5f for rounding
        }
        int scaledAmount = (int)(fAmount * *(float*)((uintptr_t)movementData + 0x04)); // +0x04: scale factor
        movementAmount = scaledAmount;
    }
    
    // Decrement timer if active
    if (*(int8_t*)((uintptr_t)thisObj + 0x1D) != 0) { // +0x1D: timer byte
        *(int8_t*)((uintptr_t)thisObj + 0x1D) -= 1;
        goto applyEffects;
    }
    
    // Obstacle/path check
    if ((flags & 0x20) != 0) {
        void* obstacle = *(void**)((uintptr_t)thisObj + 0x20); // +0x20: pointer to obstacle data
        if (obstacle == nullptr || *(int*)((uintptr_t)obstacle + 0x90) < 0) {
            bReturn0 = true;
        } else {
            float fAngle;
            float fSpeed;
            
            fAngle = (float)*(int16_t*)((uintptr_t)movementData + 0x02); // +0x02: heading angle
            if (*(int16_t*)((uintptr_t)movementData + 0x02) < 0) {
                fAngle += 0.5f;
            }
            
            fSpeed = (float)movementAmount;
            if (movementAmount < 0) {
                fSpeed += 0.5f;
            }
            
            // Call collision/validation check (likely checkObstacle)
            bool checkOk = FUN_005eb6d0(
                gEngineManager, // DAT_01223510 - pointer to engine singleton
                id,
                *(uint32_t*)((uintptr_t)thisObj + 0x0C), // +0x0C: additional ID
                *(int*)((uintptr_t)obstacle + 0x90),
                fSpeed * gSpeedScale, // DAT_00e2af48: scale factor for speed
                *(float*)((uintptr_t)movementData + 0x0C), // +0x0C: some float parameter
                fAngle * gAngleScale, // DAT_00e2af44: scale factor for angle
                (float)*(int16_t*)((uintptr_t)movementData + 0x04) * gAngleScale, // +0x04: another angle
                obstacle,
                *(uint32_t*)movementData, // +0x00: some identifier
                deltaTime
            );
            
            if (!checkOk) {
                bReturn0 = true;
            }
            
            // Clear the flag
            *(uint16_t*)((uintptr_t)thisObj + 0x10) &= 0xFEDF;
            if (*(int*)((uintptr_t)thisObj + 0x18) == 0) { // +0x18: some counter
                *(uint8_t*)((uintptr_t)thisObj + 0x1D) = 4; // Set timer to 4 frames
            }
        }
    }
    
    // Apply movement (position/velocity update)
    FUN_005dbc10(
        id,
        movementAmount,
        (int)*(int16_t*)((uintptr_t)movementData + 0x02),
        (double)*(float*)((uintptr_t)movementData + 0x0C)
    );
    
applyEffects:
    // Apply visual/state updates via engine manager virtual calls
    if ((*(uint8_t*)((uintptr_t)movementData + 0x12) & 0x1) != 0) {
        if ((*(uint8_t*)((uintptr_t)thisObj + 0x10) & 0x1) != 0) {
            *(uint16_t*)((uintptr_t)movementData + 0x04) = 0; // Reset some field
        }
        // Call engine method at vtable+0x28 (likely updateSprite/visual)
        (*(void(__thiscall**)(EngineManager*, uint16_t, int16_t*))(*((void**)gEngineManager) + 0x28))(gEngineManager, id, (int16_t*)((uintptr_t)movementData + 0x02));
    }
    
    if ((*(uint8_t*)((uintptr_t)movementData + 0x12) & 0x2) != 0) {
        // Call engine method at vtable+0x2c (likely updatePosition)
        (*(void(__thiscall**)(EngineManager*, uint16_t, int))(*((void**)gEngineManager) + 0x2C))(gEngineManager, id, movementAmount);
    }
    
    if ((*(uint8_t*)((uintptr_t)movementData + 0x13) & 0x1) != 0) {
        // Call engine method at vtable+0x30 (likely updateDirection)
        (*(void(__thiscall**)(EngineManager*, uint16_t, uint32_t))(*((void**)gEngineManager) + 0x30))(gEngineManager, id, *(uint32_t*)movementData);
    }
    
    if (bReturn0) {
        return false;
    }
    
    return true;
}