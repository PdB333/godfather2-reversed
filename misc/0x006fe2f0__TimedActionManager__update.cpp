// FUNC_NAME: TimedActionManager::update
struct TimedActionEntry {
    int32_t flags;           // +0x00, bit31 set = inactive, clear = active
    float   unknownTime;     // +0x04
    float   timer;           // +0x08
    void    (*callback)(int arg, int userData); // +0x0C
    int     userData;        // +0x10
};

void __thiscall TimedActionManager::update(float deltaTime) {
    // Check if any timed actions are active (count at +0x74)
    if (*(int*)(this + 0x74) != 0) {
        // Pointer to first timer entry's timer field (at +0x18)
        float* entryTimer = (float*)(this + 0x18);
        int entryIndex = 5; // 5 inline entries

        do {
            TimedActionEntry* entry = (TimedActionEntry*)(entryTimer - 2); // flags at -8, unknown at -4, timer at 0

            // Check entry is active (flags >= 0) and timer isn't a sentinel value
            if ((((uint)entry->flags & 0x80000000) != 0x80000000) &&
                (entry->timer != DAT_00d5f6f0)) {

                float newTimer = entry->timer - deltaTime;
                entry->timer = newTimer;

                if (newTimer <= 0.0f) {
                    // Fire callback with type 4
                    if (entry->callback != (void*)0x0) {
                        entry->callback(4, entry->userData);
                    }
                    // Deactivate entry
                    entry->flags = (int32_t)(-0.0f); // set high bit (0x80000000)
                    entry->unknownTime = 0.0f;
                    entry->timer = 0.0f;
                    entry->callback = nullptr;
                    entry->userData = 0;
                    // Decrement active count
                    *(int*)(this + 0x74) = *(int*)(this + 0x74) - 1;
                }
            }

            float threshold = DAT_00d5ef70; // global threshold for cooldown
            entryTimer = entryTimer + 5; // move to next entry (20 bytes)
            entryIndex--;
        } while (entryIndex != 0);

        // If there are still active entries, handle special cooldown timer
        if (*(int*)(this + 0x74) != 0) {
            if (*(int*)(this + 0x208) == -1) {
                // No active cooldown, check conditions at offsets 0x198 and 0x1d0
                if ((*(int*)(this + 0x198) == 0) || (*(int*)(this + 0x1d0) == 0)) {
                    TimedActionEntry* newEntry = (TimedActionEntry*)FUN_006fc350(); // allocate/get entry
                    if (newEntry != (TimedActionEntry*)0x0) {
                        if ((void*)newEntry->callback != (void*)0x0) {
                            newEntry->callback(2, newEntry->userData);
                        }
                        // Reset entry to inactive
                        newEntry->flags = 0x80000000;
                        newEntry->unknownTime = 0.0f;
                        newEntry->timer = 0.0f;
                        newEntry->callback = nullptr;
                        newEntry->userData = 0;
                    }
                }
            } else {
                // Cooldown timer active at +0x210
                float cooldownTime = *(float*)(this + 0x210) + deltaTime;
                *(float*)(this + 0x210) = cooldownTime;
                if (DAT_00d5ef70 < cooldownTime) {
                    *(int*)(this + 0x208) = -1; // deactivate cooldown
                    FUN_005e6640(&LAB_006fd640); // trigger event / finish
                }
            }
        }
    }

    // Update additional timer subsystems (three separate groups)
    FUN_006fcdd0(deltaTime);
    FUN_006fcdd0(deltaTime);
    FUN_006fcdd0(deltaTime);
}