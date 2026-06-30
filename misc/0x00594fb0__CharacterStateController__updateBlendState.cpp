// FUNC_NAME: CharacterStateController::updateBlendState
// Address: 0x00594fb0
// This function updates a blend state for a character controller, using a delta time parameter.
// It checks a global threshold and performs a complex interpolation/update if needed.
// The class has fields at offsets: 0x4e (float), 0x1f (flags), 0x20 (some pointer), 0x28 (some pointer).
// Global objects: gStateManager (at 0x012055a8) with a vtable, various global thresholds.

void CharacterStateController::update(float dt) {
    // Compute blended value from this->field_0x4e (likely a speed or blend factor)
    float blendValue = *(float*)((int)this + 0x4e * 4) * dt; // offset 0x138

    // Check against global threshold
    if (gBlendThreshold < blendValue) {
        // Complex stack-based update using virtual functions on gStateManager
        // Prepare stack variables for function calls (likely a custom calling convention)
        float* stackPtr = &blendValue;
        float* otherPtr = (float*)0x594fec; // some constant address
        // Call virtual function at vtable+0x18 on this
        (*(void(__thiscall**)(CharacterStateController*, ...))(*(int*)this + 0x18))(this, &stackPtr, otherPtr);

        // Then call various functions on gStateManager with stack arguments
        // These are likely property set/get functions
        float* localBlend = &blendValue;
        // Calls to gStateManager vtable offsets:
        // 0x14: push property
        // 0x24: set property
        // 0x10: get property
        // 0x64: some operation
        // 0x68, 0x28, 0x6c, 0x30: others

        // First push this->field_0x20 (offset 0x80) 
        int* field20 = (int*)((int)this + 0x20);
        // Call vtable+0x14 with field20
        (*(void(__thiscall**)(void*, int*))gStateManagerVtable[0x14])(gStateManager, field20);

        // Then vtable+0x24 with some stack
        // ... complicated series of pushes and pops

        // Eventually, after several calls, do a conditional:
        // vtable+0x30 returns a float10
        float randomVal = (*(float(__thiscall**)(void*, ...))gStateManagerVtable[0x30])(gStateManager, ...);
        float maxVal = gMaxBlendValue;
        if (maxVal <= randomVal) {
            randomVal = (*(float(__thiscall**)(void*, ...))gStateManagerVtable[0x30])(gStateManager, ...);
            float minVal = gMinBlendValue;
            if (randomVal <= 1.0f) {
                randomVal = (*(float(__thiscall**)(void*, ...))gStateManagerVtable[0x30])(gStateManager, ...);
                minVal = randomVal;
            }
            maxVal = minVal;
        }
        // Compute a modified value
        float modified = maxVal * gBlendFactor;
        // Compare with something (stackPtr)
        if (*(float*)otherPtr < modified) {
            // Do the full update path
            // Call vtable+0x18 on this again
            (*(void(__thiscall**)(CharacterStateController*, ...))vtable[0x18])(this, ...);
            // Call gStateManager vtable+0x68 and others
            (*(void(__thiscall**)(void*, ...))gStateManagerVtable[0x68])(gStateManager, ...);
            // ... more calls
            // Finally call vtable+0x10 and vtable+0x1c on this
            (*(void(__thiscall**)(CharacterStateController*, void*))vtable[0x10])(this, someStack);
            (*(void(__thiscall**)(CharacterStateController*, void*))vtable[0x1c])(this, someStack);
        } else {
            // Simple path: just call vtable+0x10 on gStateManager with field20
            (*(void(__thiscall**)(void*, int*))gStateManagerVtable[0x10])(gStateManager, field20);
            // Clear bit 6 of this->field_0x1f (flag)
            *(int*)((int)this + 0x1f * 4) &= ~0x40; // offset 0x7c
        }
        // Final cleanup calls
        (*(void(__thiscall**)(void*, ...))gStateManagerVtable[0x64])(gStateManager, ...);
        (*(void(__thiscall**)(CharacterStateController*, void*))vtable[0x10])(this, ...);
        (*(void(__thiscall**)(CharacterStateController*, void*))vtable[0x1c])(this, ...);
    }
    // If threshold not met, do nothing
}