//FUNC_NAME: SoundInstance::updateSpatialization
void __thiscall SoundInstance::updateSpatialization(float deltaTime) {
    // +0x5c: pointer to sound object (e.g., EARS::SoundObject*)
    int* soundObj = *(int**)(this + 0x5c);
    float maxDistance = DAT_00d7608c; // global default max distance

    // +0x74: state (2 = override max distance)
    if (*(int*)(this + 0x74) == 2) {
        // +0x78: custom max distance
        maxDistance = *(float*)(this + 0x78);
    }

    // Check if spatialization is enabled (e.g., sound system active)
    if (FUN_00875840()) {
        // Get the sound object's base volume (0-1)
        float baseVolume = (float)FUN_00870de0(soundObj);
        FUN_0086b830(baseVolume); // set volume
        FUN_0086b7f0(0);          // set pan to center

        // Get the sound's maximum audible distance (vtable+0x1b8)
        float soundMaxDist = (float)(**(code**)(*soundObj + 0x1b8))();

        // Get player position (FUN_00471610 returns player entity pointer)
        int* player = FUN_00471610();
        // +0x30, +0x34, +0x38: player position (x, y, z)
        float dx = *(float*)(this + 0x60) - *(float*)(player + 0x30);
        float dy = *(float*)(this + 0x64) - *(float*)(player + 0x34);
        float dz = *(float*)(this + 0x68) - *(float*)(player + 0x38);
        float distSq = dx*dx + dy*dy + dz*dz;

        // If within max distance and flag bit 0x10 is set (e.g., "play at full volume")
        if (distSq <= soundMaxDist * soundMaxDist && (*(byte*)(this + 0x6c) & 0x10) != 0) {
            FUN_0086b7b0(0);          // set left volume to 0
            FUN_0086b7d0(1.0f);       // set right volume to 1.0 (full)
            return;
        }

        // Compute distance-based volume/pan adjustments
        float leftVol = _DAT_00d5780c; // global left volume default
        float rightVol = 0.0f;

        // Get the sound's current distance from listener (vtable+0x1b0)
        float soundDist = (float)(**(code**)(*soundObj + 0x1b0))();

        if (soundDist <= maxDistance) {
            // Within max distance: adjust left volume based on distance falloff
            leftVol = _DAT_00d5780c;
            if (maxDistance - DAT_00d75860 < soundDist) {
                leftVol = (maxDistance - soundDist) * _DAT_00d760c0;
            }
        } else {
            // Beyond max distance: adjust right volume based on excess distance
            rightVol = (soundDist - maxDistance) * _DAT_00d760c4;
            if (_DAT_00d5780c < rightVol) {
                rightVol = _DAT_00d5780c;
            }
        }

        FUN_0086b7b0(leftVol);
        FUN_0086b7d0(rightVol);
        return;
    }

    // Fallback: use legacy spatialization (FUN_00870e60)
    FUN_00870e60(soundObj, deltaTime, maxDistance);
}