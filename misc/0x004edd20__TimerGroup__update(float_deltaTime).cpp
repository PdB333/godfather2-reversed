// FUNC_NAME: TimerGroup::update(float deltaTime)
void __thiscall TimerGroup::update(float deltaTime) {
    // +0x30: some current time marker? Set to deltaTime (maybe elapsed)
    *(float*)(this + 0x30) = deltaTime;

    // Owner object at +0x24, stores configuration and flags
    int* owner = *(int**)(this + 0x24);
    float ownerTime = *(float*)(owner + 0x94); // +0x94: threshold time

    // Global game time (DAT_00e2eff4) – likely current frame time
    if (g_currentTime < ownerTime) {
        float timer1 = *(float*)(this + 0x2c);
        if (timer1 <= ownerTime) {
            // Advance timer at +0x2c
            *(float*)(this + 0x2c) = timer1 + deltaTime;
        } else {
            // Check flag bit 0x2000 (bit 13) in owner flags at +0x2c
            if ((*(unsigned short*)(owner + 0x2c) & 0x2000) == 0) {
                deltaTime = 0.0f; // Cancel update
            } else {
                // Set a global flag to indicate something (probably pending action)
                int* tlsBase = *(int**)(__readfsdword(0x2C)); // Thread-local storage
                uint* globalFlags = (uint*)(*tlsBase + 8);    // +8 offset into engine global
                uint* flagSlot = (uint*)(*globalFlags + *(int*)(this + 0x10)); // +0x10: index into flags
                *flagSlot |= 0x20000000;
            }
        }
    }

    // Check if a global flag (bit 29) is not set – if set, skip further timer updates
    int* tlsBase = *(int**)(__readfsdword(0x2C));
    uint* globalFlags = (uint*)(*tlsBase + 8);
    uint* flagSlot = (uint*)(*globalFlags + *(int*)(this + 0x10));
    if ((*flagSlot & 0x20000000) == 0) {
        // Timer at +0x44, callback at +0x4c
        if (*(int*)(this + 0x4c) != 0) {
            // Extract bit 11 (0x800) from owner flags for callback ID
            uint callbackID = (uint)((*(unsigned short*)(owner + 0x2c) >> 11) & 1);
            *(float*)(this + 0x44) += deltaTime;
            this->notifyTimerTick(callbackID); // FUN_004edf00
        }

        // Timer at +0x50, callback at +0x58
        if (*(int*)(this + 0x58) != 0) {
            uint callbackID = (uint)((*(unsigned short*)(owner + 0x2c) >> 12) & 1);
            *(float*)(this + 0x50) += deltaTime;
            this->notifyTimerTick(callbackID);
        }

        // Additional timer at +0x34, controlled by owner flag at +0x58 and a boolean at +0x5c
        float ownerFlag = *(float*)(owner + 0x58); // +0x58 in owner: likely another threshold
        if (0.0f <= ownerFlag && *(char*)(this + 0x5c) != '\0') {
            *(float*)(this + 0x34) += deltaTime;
        }
    }

    // Implicit return
}

// Dummy helper for call – in real reconstruction this would be a private method or external
void __thiscall TimerGroup::notifyTimerTick(uint callbackID) {
    // FUN_004edf00, actual implementation unknown
}